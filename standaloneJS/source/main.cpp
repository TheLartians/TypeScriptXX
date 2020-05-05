#include <glue/emscripten/state.h>
#include <glue/view.h>
#include <greeter/glue.h>
#include <cxxopts.hpp>

#include <iostream>
#include <exception>

int main(int argc, char ** argv) {
  // parse command line options
  cxxopts::Options options("Glue Typescript Example");

  // clang-format off
  options.add_options()
    ("h,help", "Show help")
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

  // add glue to state
  glue::emscripten::State state;
  state.addModule(glue, state.root());

  // load js script
  if (opts["script"].count() > 0) {
    try {
      auto path = opts["script"].as<std::string>();
      auto mainMethod = glue::View(state.run("require(process.cwd() + '/" + path + "')"))["main"];
      mainMethod();
    } catch(const std::exception& e){
      std::cerr << e.what() << '\n';
    }
  }
  
  return 0;
}
