cmake_minimum_required (VERSION 3.2)

set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

file (GLOB_RECURSE lib_HPP ${INCLUDE_DIR}/*.h++)

add_library (ogonek SHARED ${lib_HPP})
target_link_libraries (ogonek range-v3 ogonek_ucd ogonek_codepages)
