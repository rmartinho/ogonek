cmake_minimum_required (VERSION 3.2)

set (DOC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set (DOC_FORMAT html)
set (DOC_HTML_DIR ${CMAKE_BINARY_DIR}/doc/html)
set (SPHINX_BUILD_TOOL sphinx-build)
set (SPHINX_CACHE_DIR "${CMAKE_BINARY_DIR}/_doctrees")

file (GLOB_RECURSE doc_SRC ${DOC_SRC_DIR}/*.rst)
list (REMOVE_ITEM doc_SRC "CMakeLists.txt")

add_custom_target(doc
    ${SPHINX_BUILD_TOOL}
        -q -d "${SPHINX_CACHE_DIR}"
        -b ${DOC_FORMAT}
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${DOC_HTML_DIR}"
    DEPENDS ${doc_SRC}
    COMMENT "Building HTML documentation with Sphinx")
