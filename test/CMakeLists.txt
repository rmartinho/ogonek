cmake_minimum_required (VERSION 3.2)

set (UCD_DIR ${PROJECT_SOURCE_DIR}/data/ucd)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/normalization)
set (TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/test/normalization)
set (TEST_TRANSFORM_TOOL ${PROJECT_SOURCE_DIR}/tool/transforms/normalization_tests.py)

set (normalization_test_gen_HPP ${INCLUDE_DIR}/normalization_tests.g.h++)
set (normalization_test_gen_SRC ${TEST_SRC_DIR}/normalization_tests.g.c++)

add_custom_command (
    OUTPUT ${normalization_test_gen_SRC} ${normalization_test_gen_HPP}
    COMMAND python2 ${TEST_TRANSFORM_TOOL} ${UCD_DIR}/NormalizationTest.txt ${normalization_test_gen_HPP} ${normalization_test_gen_SRC}
    DEPENDS ${TEST_TRANSFORM_TOOL}
    COMMENT "Translating normalization tests")

file (GLOB_RECURSE test_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
file (GLOB_RECURSE test_HDR ${CMAKE_CURRENT_SOURCE_DIR}/*.h++)
add_executable (test_runner ${test_SRC} ${test_HDR} ${normalization_test_gen_SRC} ${normalization_test_gen_HPP})
target_include_directories (test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (test_runner Catch ogonek_ucd ogonek_codepages)

add_custom_target(check 
    COMMAND test_runner
    DEPENDS test_runner
    COMMENT "Running all tests"
    USES_TERMINAL)
