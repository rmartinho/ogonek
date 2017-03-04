cmake_minimum_required (VERSION 3.2)

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

file (GLOB_RECURSE lib_HPP ${INCLUDE_DIR}/*.h++)
file (GLOB_RECURSE lib_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)

add_library (ogonek STATIC ${lib_SRC} ${lib_HPP})
target_link_libraries(ogonek ogonek_ucd ogonek_codepages)
