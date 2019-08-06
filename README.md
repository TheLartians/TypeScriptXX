[![Build Status](https://travis-ci.com/TheLartians/TypeScriptPP.svg?branch=master)](https://travis-ci.com/TheLartians/TypeScriptPP)

# TypeScriptPP

Example project on embedding typescript in C++ applications.

## Usage

```bash
git clone https://github.com/TheLartians/TypeScriptPP.git
cd TypeScriptPP
cmake -H. -Bbuild
cmake --build build
./build/TypeScriptPP -d # print TypeScript declarations
./build/TypeScriptPP -s lua/main.lua # run transpiled lua script
```
