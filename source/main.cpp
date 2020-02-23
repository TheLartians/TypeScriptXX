#include <FileWatcher/FileWatcher.h>
#include <glue/class_element.h>
#include <glue/declarations.h>
#include <glue/lua.h>

#include <chrono>
#include <cxxopts.hpp>
#include <iostream>
#include <string>
#include <thread>

// C++ types that are made available in Lua / TypeScript
namespace lib {

  struct A {
    int data;
    explicit A(int x) : data(x) {}
    A add(const A &other) { return A(other.data + data); }
  };

  struct B : public A {
    std::string name;
    using A::A;
  };

  // Defines the Lua / TypeScript interface for the types
  glue::Element glue() {
    glue::Element element;

    element["A"] = glue::ClassElement<lib::A>()
                       .addConstructor<int>()
                       .addMember("data", &lib::A::data)
                       .addMethod("add", &lib::A::add)
                       .addFunction("next", [](const lib::A &a) { return lib::A(a.data + 1); })
                       .addFunction("__tostring", [](const lib::A &a) {
                         return "lib::A(" + std::to_string(a.data) + ")";
                       });

    element["B"] = glue::ClassElement<lib::B>()
                       .addConstructor<int>()
                       .addMember("name", &lib::B::name)
                       .setExtends(element["A"]);

    return element;
  }

}  // namespace lib

// allow implicit casting of B to base class A in lars::Any values
LARS_ANY_DECLARE_BASES(lib::B, lib::A);

int main(int argc, char **argv) {
  // parse command line options

  cxxopts::Options options("Glue Typescript Example");
  options.add_options()("h,help", "Show help")("d,declarations", "Print typescript declarations")(
      "w,watch", "Run in watch mode")("s,script",
                                      "path to the main directory containing an index.lua script",
                                      cxxopts::value<std::string>());

  auto opts = options.parse(argc, argv);

  if (opts.arguments().size() == 0 || opts["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  // create glue

  glue::Element glue;
  glue["log"] = [](std::string message) { std::cout << "logged: " << message << std::endl; };
  glue["lib"] = lib::glue();

  // print the TypeScript declarations on demand.
  // Used by the project's CMakeLists to create the declarations file.
  if (opts["declarations"].as<bool>()) {
    std::cout << glue::getTypescriptDeclarations("glue", glue) << std::endl;
  }

  // run lua
  if (opts["script"].count() > 0) {
    auto path = opts["script"].as<std::string>();

    auto runMainScript = [&](const std::string &path) {
      glue::LuaState lua;
      lua.openStandardLibs();
      lua["glue"] = glue;
      lua["package"]["path"] = path + "/?.lua;" + path + "/?/index.lua;";

      auto mainMethod
          = lua.run("return require('.')").get<glue::Map &>()["main"].get<lars::AnyFunction>();

      lars::AnyArguments args;
      auto result = mainMethod.call(args);
      if (result) {
        return result.get<int>();
      } else {
        // implicitly return 0
        return 0;
      }
    };

    if (opts["watch"].count() > 0) {
      std::cout << "Enter watch mode. watching: " << path << std::endl;
      struct ChangeListener : public FW::FileWatchListener {
        bool changed;
        void handleFileAction(FW::WatchID, const FW::String &, const FW::String &, FW::Action) {
          changed = true;
        }
      } listener;
      FW::FileWatcher fileWatcher;
      fileWatcher.addWatch(path, &listener, true);
      while (true) {
        listener.changed = false;
        fileWatcher.update();
        if (listener.changed) {
          try {
            runMainScript(path);
          } catch (const std::exception &e) {
            std::cerr << e.what() << '\n';
          }
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
      }
    } else {
      return runMainScript(path);
    }
  }

  return 0;
}
