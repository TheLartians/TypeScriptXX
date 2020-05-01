
#include <greeter/greeter.h>
#include <greeter/glue.h>
#include <glue/class.h>
#include <glue/enum.h>

glue::MapValue greeter::glue() {
  auto lib = glue::createAnyMap();

  lib["Greeter"] = glue::createClass<Greeter>()
    .addConstructor<std::string>()
    .addMethod("greet", &Greeter::greet)
  ;

  lib["LanguageCode"] = glue::createEnum<LanguageCode>()
  .addValue("EN", LanguageCode::EN)
  .addValue("DE", LanguageCode::DE)
  .addValue("ES", LanguageCode::ES)
  .addValue("FR", LanguageCode::FR)
  ;

  return lib;
}
