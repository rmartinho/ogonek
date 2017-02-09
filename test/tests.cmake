cmake_minimum_required (VERSION 3.2)

macro (add_test_library list_var DIR)
    set (result ${${list_var}})

    file (GLOB_RECURSE ${DIR}_test_SRC ${DIR}/*.c++)
    add_library (${DIR}_test ${${DIR}_test_SRC})
    target_include_directories (${DIR}_test PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    target_link_libraries (${DIR}_test Catch ${ARGN})

    list (APPEND result ${DIR}_test)
    set (${list_var} ${result} PARENT_SCOPE)
endmacro ()
