cmake_minimum_required (VERSION 3.2)

set (test_runner runner.c++)

macro (add_test_executable DIR)
    file (GLOB_RECURSE ${DIR}_test_SRC ${DIR}/*.c++)
    add_executable (${DIR}_test ${test_runner} ${${DIR}_test_SRC})
    target_include_directories (${DIR}_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries (${DIR}_test Catch ${ARGN})
endmacro ()

add_test_executable (ucd ogonek_data)
add_test_executable (encoding range-v3)
