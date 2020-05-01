cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(TypeScriptXX
  LANGUAGES CXX
)

# --- Import tools ----

include(../cmake/tools.cmake)

# ---- Dependencies ----

include(../cmake/CPM.cmake)

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
  GITHUB_REPOSITORY apetrone/simplefilewatcher
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
  NAME Greeter
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..
)

CPMAddPackage(
  NAME TypeScriptXXDeclarations
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../declarations
)

CPMAddPackage(
  NAME LuaGlue
  VERSION 1.0
  GITHUB_REPOSITORY TheLartians/LuaGlue
)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(TypeScriptXX ${sources})

set_target_properties(TypeScriptXX PROPERTIES 
  CXX_STANDARD 17 
  OUTPUT_NAME "TypeScriptXX"
)

target_link_libraries(TypeScriptXX Greeter LuaGlue cxxopts FileWatcher)

# ---- Create typescript declarations ----

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
  DEPENDS TypeScriptXXDeclarations
  COMMAND TypeScriptXXDeclarations > ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
  WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  COMMENT "update typescript declarations"
)

# ---- Compile typescript code ----

include(${LuaGlue_SOURCE_DIR}/cmake/TranspileTypeScript.cmake)

TranspileTypeScript(
  NAME TypeScriptXX
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..
  RESULT ${CMAKE_CURRENT_SOURCE_DIR}/../lua
  COMMAND build
  DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../typescript/cpplib.d.ts
)

add_custom_target(BuildTypeScript ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/../lua)
