cmake_minimum_required (VERSION 2.6)
project (BetterAlgebraSystem)

# The version number.
set (BAS_VERSION_MAJOR 0)
set (BAS_VERSION_MINOR 1)

macro(use_c99)
  if (CMAKE_VERSION VERSION_LESS "3.1")
    if (CMAKE_C_COMPILER_ID STREQUAL "GNU")
      set (CMAKE_C_FLAGS "--std=gnu99 ${CMAKE_C_FLAGS}")
    endif ()
  else ()
    set (CMAKE_C_STANDARD 99)
  endif ()
endmacro(use_c99)
use_c99()

file(GLOB Sources "src/*.c")
message("Source Paths: " ${Sources})

file(GLOB TestSources "src/*.c" "tests/*.c")
file(GLOB TestHeaders "src/*.h")
list(REMOVE_ITEM TestSources "${CMAKE_SOURCE_DIR}/src/main.c")
message("Excluding from testexe: " "${CMAKE_SOURCE_DIR}/src/main.c")
message("Test Source Paths: " ${TestSources})
#message("Test Header Paths: " ${TestHeaders})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)



add_executable(bas ${Sources})
add_executable(testexe ${TestSources})
target_include_directories(testexe PRIVATE "${CMAKE_SOURCE_DIR}/src/")
target_compile_definitions(testexe PRIVATE TEST=1)

enable_testing()
add_test(NAME Test COMMAND testexe)

add_custom_target(test-verbose COMMAND ${CMAKE_CTEST_COMMAND} --verbose)
