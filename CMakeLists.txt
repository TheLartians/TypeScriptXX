cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(TypeScriptPP)

add_executable(TypeScriptPP source/main.cpp)
set_target_properties(TypeScriptPP PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")

# ---- Add dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Glue
  VERSION 0.9.5
  GIT_TAG 07d53dc6b254918a3a504aeb04403d3c1eb2b6da
  GIT_REPOSITORY https://github.com/TheLartians/Glue.git
  OPTIONS
    "GLUE_ENABLE_LUA YES"
    "GLUE_BUILD_LUA YES"
)

CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.0
  OPTIONS
    "CXXOPTS_BUILD_EXAMPLES Off"
    "CXXOPTS_BUILD_TESTS Off"
)

target_link_libraries(TypeScriptPP Glue cxxopts)

# ---- Create typescript declarations ----

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/typescript/lib.d.ts
  DEPENDS TypeScriptPP
  COMMAND TypeScriptPP -d > ${CMAKE_CURRENT_SOURCE_DIR}/typescript/lib.d.ts
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "update typescript declarations"
)
ADD_CUSTOM_TARGET(update-declarations DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/typescript/lib.d.ts)

# ---- Compile typescript code ----

GlueCreateTypescriptTarget(compile-typescript ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lua)
add_dependencies(compile-typescript update-declarations)
