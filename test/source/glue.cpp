#include <doctest/doctest.h>
#include <glue/context.h>
#include <glue/view.h>
#include <greeter/glue.h>

TEST_CASE("Glue bindings") {
  glue::Context context;
  auto greeterGlue = greeter::glue();
  auto view = glue::View(greeterGlue);
  context.addRootMap(greeterGlue);
  auto instance = context.createInstance(view["Greeter"][glue::keys::constructorKey]("Glue"));
  REQUIRE(instance);
  CHECK(instance["greet"](*view["LanguageCode"]["EN"]).as<std::string>() == "Hello, Glue!");
}
