# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Vole-Machine-GUI_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Vole-Machine-GUI_autogen.dir\\ParseCache.txt"
  "Vole-Machine-GUI_autogen"
  )
endif()
