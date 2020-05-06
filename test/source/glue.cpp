#include <doctest/doctest.h>
#include <glue/context.h>
#include <greeter/glue.h>

TEST_CASE("Glue bindings") {
  glue::Context context;
  auto greeterGlue = greeter::glue();
  context.addRootMap(greeterGlue);
  auto greeterInstance
      = context.createInstance(greeterGlue["Greeter"][glue::keys::constructorKey]("Glue"));
  REQUIRE(greeterInstance);
  CHECK(greeterInstance["greet"](greeterGlue["LanguageCode"]["EN"]).as<std::string>()
        == "Hello, Glue!");
}
