cmake_minimum_required (VERSION 3.2)

set (UCD_DIR ${PROJECT_SOURCE_DIR}/data/ucd)
set (NORM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/normalization)
set (NORM_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/test/normalization)
set (NORM_TEST_TRANSFORM_TOOL ${PROJECT_SOURCE_DIR}/tool/transforms/normalization_tests.py)
set (SEGM_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/test/segmentation)
set (SEGM_TEST_SRC_DIR ${PROJECT_SOURCE_DIR}/test/segmentation)
set (SEGM_TEST_TRANSFORM_TOOL ${PROJECT_SOURCE_DIR}/tool/transforms/segmentation_tests.py)

set (normalization_test_gen_HPP ${NORM_INCLUDE_DIR}/normalization_tests.g.h++)
set (normalization_test_gen_SRC ${NORM_TEST_SRC_DIR}/normalization_tests.g.c++)

add_custom_command (
    OUTPUT ${normalization_test_gen_SRC} ${normalization_test_gen_HPP}
    COMMAND python2 ${NORM_TEST_TRANSFORM_TOOL} ${UCD_DIR}/NormalizationTest.txt ${normalization_test_gen_HPP} ${normalization_test_gen_SRC}
    DEPENDS ${NORM_TEST_TRANSFORM_TOOL}
    COMMENT "Translating normalization tests")

set (segmentation_test_gen_HPP ${SEGM_INCLUDE_DIR}/segmentation_tests.g.h++)
set (grapheme_test_gen_SRC ${SEGM_TEST_SRC_DIR}/grapheme_cluster_tests.g.c++)
set (word_test_gen_SRC ${SEGM_TEST_SRC_DIR}/word_tests.g.c++)
set (sentence_test_gen_SRC ${SEGM_TEST_SRC_DIR}/sentence_tests.g.c++)
set (line_test_gen_SRC ${SEGM_TEST_SRC_DIR}/line_tests.g.c++)
set (segmentation_test_gen_SRC ${grapheme_test_gen_SRC} ${word_test_gen_SRC} ${sentence_test_gen_SRC} ${line_test_gen_SRC})
set (segmentation_test_in_SRC ${UCD_DIR}/auxiliary/GraphemeBreakTest.txt ${UCD_DIR}/auxiliary/WordBreakTest.txt ${UCD_DIR}/auxiliary/SentenceBreakTest.txt ${UCD_DIR}/auxiliary/LineBreakTest.txt)

add_custom_command (
    OUTPUT ${segmentation_test_gen_SRC} ${segmentation_test_gen_HPP}
    COMMAND python ${SEGM_TEST_TRANSFORM_TOOL} ${segmentation_test_in_SRC} ${segmentation_test_gen_HPP} ${segmentation_test_gen_SRC}
    DEPENDS ${SEGM_TEST_TRANSFORM_TOOL}
    COMMENT "Translating segmentation tests")

file (GLOB_RECURSE test_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
file (GLOB_RECURSE test_HDR ${CMAKE_CURRENT_SOURCE_DIR}/*.h++)
add_executable (test_runner ${test_SRC} ${test_HDR} ${normalization_test_gen_SRC} ${normalization_test_gen_HPP} ${segmentation_test_gen_HPP} ${segmentation_test_gen_SRC})
target_include_directories (test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (test_runner Catch range-v3 ogonek)

add_custom_target(check 
    COMMAND test_runner
    DEPENDS test_runner
    COMMENT "Running all tests"
    USES_TERMINAL)
