[![Build Status](https://travis-ci.com/TheLartians/TypeScriptPP.svg?branch=master)](https://travis-ci.com/TheLartians/TypeScriptPP)

# TypeScriptPP

Example project showing to embed the [TypeScript](https://www.typescriptlang.org) scripting language in a C++ project.
[TypeScriptToLua](https://github.com/TypeScriptToLua/TypeScriptToLua) is used to transpile TypeScript code to Lua that is embedded via [Glue](https://github.com/TheLartians/Glue).
CMake is used to track dependencies and initialize or compile TypeScript when needed. 
Declarations for the C++ interface can be generated automatically from Glue elements.

## Usage

```bash
git clone https://github.com/TheLartians/TypeScriptPP.git
cd TypeScriptPP
cmake -H. -Bbuild
cmake --build build -j4 # compiles C++, creates declarations and compiles TypeScript sources
./build/TypeScriptPP -d # print TypeScript declarations
./build/TypeScriptPP -s lua # run transpiled lua script
```

## Recompile TypeScript without CMake

```bash
npm run build
```

## Only update declarations

```bash
cmake --build build --target update-declarations
```
