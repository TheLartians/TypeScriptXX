[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Lua/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/JavaScript/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Test/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Check%20style/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)

# TypeScriptXX

## About

This is a template project that uses the [Glue](https://github.com/TheLartians/Glue) library to add type-safe scripting capability to a C++ project.
Scrips are coded in [TypeScript](https://www.typescriptlang.org), transpiled using [TSTL](https://typescripttolua.github.io) and run in an embedded [Lua](https://www.lua.org) engine.
The TypeScript declarations are automatically generated and updated by CMake. 

## Usage

The following commands build the project and run the [typescript script](typescript/index.ts).

```bash
cmake -HstandaloneLua -Bbuild

 # Compiles C++ code, updates the declarations and transpiles TypeScript
cmake --build build -j8

# runs the transpiled lua script at lua/index.lua
./build/TypeScriptXX --script lua 
```

Is is also possible to enable watch mode for hot reloading.

```bash
npx concurrently "npm run watch:lua" "./build/TypeScriptXX -s lua --watch"
```

## How it works

The example C++ [library](include/greeter/greeter.h) is exposed to TypeScript using [Glue bindings](source/glue.cpp).
The projects contains two standalone subprojects: [one](standaloneLua) that uses [LuaGlue](https://github.com/TheLartians/LuaGlue) to bind and run lua code and [one](declarations) that simply prints the declarations.
After building, CMake will use the latter to ensure that the declarations at `typescript/cpplib.d.ts` are up-to-date and then transpile the TypeScript code to Lua.
