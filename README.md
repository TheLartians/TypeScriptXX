[![Build Status](https://travis-ci.com/TheLartians/TypeScriptPP.svg?branch=master)](https://travis-ci.com/TheLartians/TypeScriptPP)

# TypeScriptPP

Example project showing how to embed the [TypeScript](https://www.typescriptlang.org) scripting language in a C++ project with automatically generated declarations.

## Motivation

Lua is a great embedded scripting language for C++ projects. 
Unfortunately, Lua code becomes unmaintainable the project grows, due to the absence of reliable static type checkers. 
In the JavaScript world this was solved a long time ago with through the [TypeScript](https://www.typescriptlang.org) language.
Thanks to the great work of [TypeScriptToLua](https://typescripttolua.github.io) project, it is now possible to use TypeScript for Lua projects.
This project demonstrates how to use CMake to bring TypeScript, Lua and C++ together and can be used as inspiration or a starting point for further projects.

## Usage

```bash
git clone https://github.com/TheLartians/TypeScriptPP.git
cd TypeScriptPP
cmake -H. -Bbuild
cmake --build build -j4 # compiles C++, updates lib.d.ts and transpiles TypeScript
./build/TypeScriptPP -d # print TypeScript declarations
./build/TypeScriptPP -s lua # runs the transpiled lua script lua/index.lua 
```

## How it works

The C++ project is contained in [source/main.cpp](source/main.cpp) which contains the C++ library and a Lua interface.
It also defines a simple CLI for generating and printing the declarations and executing a lua script.

CMake uses [CPM](https://github.com/TheLartians/CPM) and [npm](https://www.npmjs.com) to download and configure all dependencies in the current directory.
After building the C++ code, CMake uses the executable to update the TypeScript [declarations](typescript/cpplib.d.ts) and then transpiles the TypeScript code to Lua with TypeScriptToLua. 

CMake also adds `package.json` and the TypeScript sources to the dependency to automatically re-invoke TypeScriptToLua on changes.
The TypeScript sources are collected using `GLOB`, so be sure to re-run `cmake` after adding new source files.

## Additional commands

### Recompile TypeScript without invoking CMake

```bash
npm run build
```

### Manually update the declarations

```bash
cmake --build build --target update-declarations
```
