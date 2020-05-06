cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(TypeScriptXX
  LANGUAGES CXX
)

# --- Import tools ----

include(../cmake/tools.cmake)

# --- Set CMake flags

# disable closure as it currently breaks the script
set(CMAKE_CXX_FLAGS_RELEASE "-Oz -g0 --llvm-lto 3 --closure 0")
set(CMAKE_CXX_FLAGS "-s DISABLE_EXCEPTION_CATCHING=0")

# ---- Dependencies ----

include(../cmake/CPM.cmake)

CPMAddPackage(
  NAME Greeter
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

CPMAddPackage(
  NAME cxxopts
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 2.2.0
  OPTIONS
    "CXXOPTS_BUILD_EXAMPLES NO"
    "CXXOPTS_BUILD_TESTS NO"
)

CPMAddPackage(
  NAME EmGlue
  VERSION 0.2
  GITHUB_REPOSITORY TheLartians/EmGlue
)

CPMAddPackage(
  NAME TypeScriptXXDeclarations
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../declarations
)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(TypeScriptXX ${sources})

set_target_properties(TypeScriptXX PROPERTIES 
  CXX_STANDARD 17 
  OUTPUT_NAME "TypeScriptXX"
)

target_link_libraries(TypeScriptXX Greeter EmGlue cxxopts)

# ---- Create typescript declarations ----

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
  DEPENDS TypeScriptXXDeclarations
  COMMAND node ${TypeScriptXXDeclarations_BINARY_DIR}/TypeScriptXXDeclarations.js > ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  COMMENT "update typescript declarations"
)

# ---- Compile typescript code ----

include(../cmake/TranspileTypeScript.cmake)

TranspileTypeScript(
  NAME TypeScriptXX
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  RESULT ${CMAKE_CURRENT_SOURCE_DIR}/../dist/js
  COMMAND build:js
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
)

add_custom_target(BuildTypeScript ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../dist/js)
