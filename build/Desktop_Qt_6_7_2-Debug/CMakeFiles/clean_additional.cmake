# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "BitFlip_autogen"
  "CMakeFiles/BitFlip_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/BitFlip_autogen.dir/ParseCache.txt"
  )
endif()
