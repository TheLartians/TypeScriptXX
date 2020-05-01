cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(TypeScriptXXDeclarations
  LANGUAGES CXX
)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME Greeter
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(TypeScriptXXDeclarations ${sources})

set_target_properties(TypeScriptXXDeclarations PROPERTIES CXX_STANDARD 17)
target_link_libraries(TypeScriptXXDeclarations Greeter)
