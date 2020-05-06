[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Lua/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/JavaScript/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Test/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)
[![Actions Status](https://github.com/TheLartians/TypeScriptXX/workflows/Check%20style/badge.svg)](https://github.com/TheLartians/TypeScriptXX/actions)

# TypeScriptXX

## About

This is a template project that uses the [Glue](https://github.com/TheLartians/Glue) library to add type-safe scripting capability to a C++ project.
Scrips are coded in [TypeScript](https://www.typescriptlang.org), transpiled using [tsc](https://www.typescriptlang.org/docs/handbook/compiler-options.html) or [TSTL](https://typescripttolua.github.io) and run in by [node.js](https://nodejs.org) or an an embedded [Lua](https://www.lua.org) engine.
The built JavaScript target can also be run in a browser and used on a website.
The TypeScript declarations are automatically generated and updated by CMake. 

## Usage

### Transpile to Lua and run natively

The following commands build the project and run the [typescript script](typescript/index.ts).

```bash
cmake -HstandaloneLua -Bbuild/lua

 # Compiles C++ code, updates the declarations and transpiles TypeScript
cmake --build build/lua -j8

# runs the transpiled lua script at dist/lua/index.lua
./build/lua/TypeScriptXX --script dist/lua 
```

Is is also possible to enable watch mode for hot reloading.
This way any code changes to the TypeScript source will be transpiled and run automatically.

```bash
npx concurrently "npm run watch:lua" "./build/lua/TypeScriptXX -s dist/lua --watch"
```

### Transpile to JavaScript and run in node.js

First, [install and activate](https://emscripten.org/docs/getting_started/downloads.html) the emsdk.
The following commands build the project and run the [typescript script](typescript/index.ts).

```bash
emcmake cmake -HstandaloneJS -Bbuild/js

 # Compiles C++ code, updates the declarations and transpiles TypeScript
cmake --build build/js -j8

# runs the transpiled lua script at dist/js/index.js
node ./build/js/TypeScriptXX.js --script dist/js 
```

### How it works

The example C++ [library](include/greeter/greeter.h) is exposed to TypeScript using [Glue bindings](source/glue.cpp).

The projects contains four standalone subprojects:

- [test](test) check the library code and run tests
- [declarations](declarations) that simply prints the declarations
- [standaloneLua](standaloneLua) that uses [LuaGlue](https://github.com/TheLartians/LuaGlue) to bind and run lua code.
- [standaloneJS](standaloneLua) that uses [EmGlue](https://github.com/TheLartians/EmGlue) to bind to a JavaScript runtime such as node.js.

After building, CMake will use the latter to ensure that the declarations at `typescript/cpplib.d.ts` are up-to-date and then transpile the TypeScript code to Lua or JavaScript.
