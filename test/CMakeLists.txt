cmake_minimum_required (VERSION 3.2)

include (tests.cmake)

file (GLOB_RECURSE test_SRC ${CMAKE_CURRENT_SOURCE_DIR}/*.c++)
add_executable (test_runner ${test_SRC})
target_include_directories (test_runner PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries (test_runner Catch ogonek_ucd ogonek_codepages)

add_custom_target(check 
    COMMAND test_runner
    DEPENDS test_runner
    COMMENT "Running all tests"
    USES_TERMINAL)
