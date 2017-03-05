cmake_minimum_required (VERSION 3.2)

project (Ogonek)
include (deps/catch.cmake)
include (deps/range-v3.cmake)

set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set (CMAKE_CXX_COMPILER clang++)
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_definitions(/W4)
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-Wall -Wextra -pedantic -Werror)
endif()

set (OGONEK_ABI abiv0)

include_directories (${PROJECT_SOURCE_DIR}/include)

add_subdirectory (src/ucd)
add_subdirectory (src/encodings)
add_subdirectory (src)
add_subdirectory (test)
add_subdirectory (doc)
