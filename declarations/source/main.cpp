#include <glue/context.h>
#include <glue/declarations.h>
#include <greeter/glue.h>

#include <iostream>

int main() {
  auto glue = glue::createAnyMap();
  glue["greeter"] = greeter::glue();

  // dummy function for declarations, will be implemented by the runtime
  glue["deleteValue"] = [](glue::Any) {};

  glue::Context context;
  context.addRootMap(glue);

  glue::DeclarationPrinter printer;
  printer.init();
  printer.print(std::cout, glue, &context);
  std::cout << std::endl;

  return 0;
}
