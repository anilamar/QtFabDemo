# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FABDemo_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FABDemo_autogen.dir\\ParseCache.txt"
  "FABDemo_autogen"
  )
endif()
