cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

project(TypeScriptPP)

add_executable(TypeScriptPP source/main.cpp)
set_target_properties(TypeScriptPP PROPERTIES CXX_STANDARD 17 COMPILE_FLAGS "-Wall -pedantic -Wextra -Werror")

# ---- Add dependencies ----

include(cmake/CPM.cmake)

CPMAddPackage(
  NAME Glue
  VERSION 0.9.6
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
    "CXXOPTS_BUILD_EXAMPLES NO"
    "CXXOPTS_BUILD_TESTS NO"
)

CPMAddPackage(
  NAME FileWatcher
  GIT_TAG ee0b97efd206282ef8bb4b9c10c90c941de4a52b
  GIT_REPOSITORY https://github.com/apetrone/simplefilewatcher.git
)

if (FileWatcher_ADDED)
  file (GLOB FileWatcherSources ${FileWatcher_SOURCE_DIR}/source/*.cpp)
  add_library(FileWatcher ${FileWatcherSources})
  target_include_directories(FileWatcher PUBLIC ${FileWatcher_SOURCE_DIR}/include)
  
  install(
    TARGETS FileWatcher
    ARCHIVE DESTINATION lib
  )
endif()

CPMAddPackage(
  NAME Format.cmake
  GITHUB_REPOSITORY TheLartians/Format.cmake
  VERSION 1.0
)

target_link_libraries(TypeScriptPP Glue cxxopts FileWatcher)

# ---- Create typescript declarations ----

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/typescript/cpplib.d.ts
  DEPENDS TypeScriptPP
  COMMAND TypeScriptPP -d > ${CMAKE_CURRENT_SOURCE_DIR}/typescript/cpplib.d.ts
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  COMMENT "update typescript declarations"
)

# ---- Compile typescript code ----

GlueBuildTypescript(
  NAME TypeScriptPP
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  RESULT ${CMAKE_CURRENT_SOURCE_DIR}/lua
  COMMAND build
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/typescript/cpplib.d.ts
)

add_custom_target(BuildTypeScript ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/lua)
