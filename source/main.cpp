#include <glue/class_element.h>
#include <glue/declarations.h>
#include <glue/lua.h>
#include <iostream>
#include <string>
#include <cxxopts.hpp>

namespace lib {
  
  struct A {
    int data;
    explicit A(int x):data(x){}
    A add(const A &other){ return A(other.data + data); }
  };

  struct B: public A {
    std::string name;
    using A::A;
  };

}

// allow implicit casting of B to base class A in lars::Any values
LARS_ANY_DECLARE_BASES(lib::B, lib::A);

int main(int argc, char ** argv) {

  // parse command line options

  cxxopts::Options options("Glue Typescript Example");
  options.add_options()
    ("h,help", "Show help")
    ("d,declarations", "Print typescript declarations")
    ("s,script", "path to the main directory containing an index.lua script", cxxopts::value<std::string>());

  auto opts = options.parse(argc, argv);

  if (opts.arguments().size() == 0 || opts["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  // define C++ <-> TypeScript Interface via Glue::Elements

  glue::Element lib;

  lib["log"] = [](std::string message){ 
    std::cout << "logged: " << message << std::endl;
  };

  lib["A"] = glue::ClassElement<lib::A>()
  .addConstructor<int>()
  .addMember("data", &lib::A::data)
  .addMethod("add", &lib::A::add)
  .addFunction("next", [](const lib::A &a){ return lib::A(a.data+1); })
  .addFunction("__tostring", [](const lib::A &a){ return "lib::A(" + std::to_string(a.data) + ")"; })
  ;

  lib["B"] = glue::ClassElement<lib::B>()
  .addConstructor<int>()
  .addMember("name", &lib::B::name)
  .setExtends(lib["A"])
  ;

  if (opts["declarations"].as<bool>()) {
    std::cout << glue::getTypescriptDeclarations("lib", lib) << std::endl;
  }

  // run lua
  
  if (opts["script"].count() > 0) {
    auto path = opts["script"].as<std::string>();
    glue::LuaState lua;
    lua.openStandardLibs();
    lua["lib"] = lib;
    lua["package"]["path"] = path + "/?.lua;" + path + "/?/index.lua;";
    lua.runFile(path + "/index.lua");
  }
  
  return 0;
}
