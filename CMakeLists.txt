cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(
  Greeter
  VERSION 1.0
  LANGUAGES CXX  
)

# ---- Add Tools ----

include(cmake/tools.cmake)

# ---- Dependencies ----

include(cmake/CPM.cmake)

# helper to create an installable target
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.2
)

CPMAddPackage(
  NAME Glue
  VERSION 1.3.2
  GITHUB_REPOSITORY TheLartians/Glue
)

# ---- Add source files ----

FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

add_library(Greeter ${headers} ${sources})

set_target_properties(Greeter PROPERTIES CXX_STANDARD 17)

# beeing a cross-platform target, we enforce enforce standards conformance on MSVC
target_compile_options(Greeter PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

target_link_libraries(Greeter PUBLIC Glue)

target_include_directories(Greeter
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  DEPENDENCIES Glue
)
