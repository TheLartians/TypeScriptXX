cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(TypeScriptPP)

add_executable(TypeScriptPP source/main.cpp)
set_target_properties(TypeScriptPP PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Glue
  VERSION 0.9.3
  GIT_TAG 3acce9d0af279bbf8c810a1a5aebed440b4505a1
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

GlueCreateTypescriptTarget(CompileTypescript ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/lua)
add_dependencies(TypeScriptPP CompileTypescript)
