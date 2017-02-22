cmake_minimum_required (VERSION 3.2)

set (DOC_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})

if (DEFINED ENV{DOC_FORMAT})
    set (DOC_FORMAT "$ENV{DOC_FORMAT}")
else ()
    set (DOC_FORMAT html)
endif ()

set (DOC_OUT_DIR ${CMAKE_BINARY_DIR}/doc/${DOC_FORMAT})
set (SPHINX_BUILD_TOOL sphinx-build)
set (SPHINX_CACHE_DIR ${CMAKE_BINARY_DIR}/_doctrees)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include/ogonek)
set (AUTODOC_SCRIPT ${PROJECT_SOURCE_DIR}/tool/extract-docs.awk)

file (GLOB_RECURSE doc_SRC ${DOC_SRC_DIR}/*.rst)

file (GLOB_RECURSE headers_SRC ${INCLUDE_DIR}/*.h++)

foreach (header ${headers_SRC})
    file (RELATIVE_PATH short_header ${INCLUDE_DIR} ${header})
    if ((${short_header} MATCHES "\\.g\\.h\\+\\+$")
     OR (${short_header} MATCHES "^detail/")
     OR (${short_header} MATCHES "^encodings/"))
        list (REMOVE_ITEM headers_SRC ${header})
    endif ()
endforeach ()

function (extract_docs out_var)
    set (result)
    foreach (header ${ARGN})
        file (RELATIVE_PATH short_header ${INCLUDE_DIR} ${header})
        string (REGEX MATCH "^(.*)\\.[^.]*$" dummy ${short_header})
        set (extracted ${CMAKE_CURRENT_SOURCE_DIR}/extracted/${CMAKE_MATCH_1}.g.rst)

        add_custom_command (OUTPUT ${extracted}
            COMMAND awk -f ${AUTODOC_SCRIPT} ${header} > ${extracted}
            COMMAND [ -s ${extracted} ] || rm -f ${extracted}
            DEPENDS ${header} ${AUTODOC_SCRIPT}
            COMMENT "Extracting inline documentation from ${short_header}"
        )
        list (APPEND result ${extracted})
  endforeach ()

  set (${out_var} ${result} PARENT_SCOPE)
endfunction ()

function (get_doc_outputs out_var)
    set (result)
    foreach (rst ${ARGN})
        file (RELATIVE_PATH compiled ${CMAKE_CURRENT_SOURCE_DIR} ${rst})
        string (REGEX MATCH "^(.*)\\.[^.]*$" dummy ${compiled})
        set (compiled ${CMAKE_BINARY_DIR}/doc/${CMAKE_MATCH_1}.html) # TODO non-HTML stuff?
        list (APPEND result ${compiled})
  endforeach ()

  set (${out_var} ${result} PARENT_SCOPE)
endfunction ()

get_doc_outputs (docs_OUT ${doc_SRC})
extract_docs (extracted_docs_SRC ${headers_SRC})

add_custom_command (OUTPUT ${docs_OUT}
    COMMAND ${SPHINX_BUILD_TOOL} -q -a -E
        -d ${SPHINX_CACHE_DIR}
        -b ${DOC_FORMAT}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${DOC_OUT_DIR}
    DEPENDS ${doc_SRC} ${extracted_docs_SRC}
    COMMENT "Building ${DOC_FORMAT} documentation with Sphinx"
)

add_custom_target (doc DEPENDS ${docs_OUT})
