#include <glue/lua/state.h>
#include <glue/view.h>
#include <cxxopts.hpp>
#include <greeter/glue.h>

#include "watch.h"

int main(int argc, char **argv) {

  // parse command line options
  cxxopts::Options options("Glue Typescript Example");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
    ("d,declarations", "Print typescript declarations")
    ("w,watch", "Run in watch mode")
    ("s,script", "path to a lua script or a directory containing an `index.lua` script", cxxopts::value<std::string>());
  // clang-format on

  auto opts = options.parse(argc, argv);

  if (opts.arguments().size() == 0 || opts["help"].as<bool>()) {
    std::cout << options.help() << std::endl;
    return 0;
  }

  // create glue
  auto glue = glue::createAnyMap();
  glue["greeter"] = greeter::glue();

  // run lua
  if (opts["script"].count() > 0) {
    auto path = opts["script"].as<std::string>();

    auto runMainScript = [&]() {
      // create Lua state
      glue::lua::State lua;
      lua.openStandardLibs();
      
      // add Glue and set include path
      lua.addModule(glue);
      lua.root()["package"].asMap()["path"] = path + "/?.lua;" + path + "/?/index.lua;";

      // load the script from the path via require
      auto result = *glue::View(lua.run("return require('.')"))["main"]();
      return result.get<int>();
    };

    if (opts["watch"].count() > 0) {
      return watch(path, runMainScript);
    } else {
      return runMainScript();
    }
  }

  return 0;
}
