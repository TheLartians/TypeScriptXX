
function(TranspileTypeScript) 

  set(oneValueArgs
    NAME
    DIRECTORY
    RESULT
    COMMAND
  )

  set(multiValueArgs
    DEPENDS
  )

  cmake_parse_arguments(TS_ARGS "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

  ADD_CUSTOM_COMMAND(
    OUTPUT ${TS_ARGS_DIRECTORY}/node_modules
    DEPENDS ${TS_ARGS_DIRECTORY}/package.json
    COMMAND npm install
    COMMAND touch node_modules
    WORKING_DIRECTORY ${TS_ARGS_DIRECTORY}
  )

  file(GLOB_RECURSE typescriptSources CONFIGURE_DEPENDS "${TS_ARGS_DIRECTORY}/*.ts")

  ADD_CUSTOM_COMMAND(
    OUTPUT ${TS_ARGS_RESULT}
    DEPENDS ${TS_ARGS_DIRECTORY} "${TS_ARGS_DIRECTORY}/tsconfig.json" ${TS_ARGS_DIRECTORY}/node_modules ${TS_ARGS_DEPENDS} ${typescriptSources}
    COMMAND npm run ${TS_ARGS_COMMAND}
    COMMAND touch ${TS_ARGS_RESULT}
    WORKING_DIRECTORY ${TS_ARGS_DIRECTORY}
  )

endfunction()
