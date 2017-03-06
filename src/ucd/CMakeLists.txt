cmake_minimum_required (VERSION 3.2)

set (UCD_DIR ${PROJECT_SOURCE_DIR}/data/ucd)
set (INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set (UCD_SRC_DIR ${PROJECT_SOURCE_DIR}/src/ucd/gen)
set (UCD_TRANSFORM_TOOL ${PROJECT_SOURCE_DIR}/tool/transforms/ucd.py)

file (GLOB_RECURSE ucd_txt_SRC ${UCD_SRC_DIR}/*.c++)

execute_process (
    COMMAND python ${UCD_TRANSFORM_TOOL} --files ${INCLUDE_DIR} ${UCD_SRC_DIR}
    OUTPUT_VARIABLE ucd_gen_SRC)

add_custom_command (
    OUTPUT ${ucd_gen_SRC}
    COMMAND python ${UCD_TRANSFORM_TOOL} ${OGONEK_ABI} ${UCD_DIR} ${INCLUDE_DIR} ${UCD_SRC_DIR}
    DEPENDS ${UCD_TRANSFORM_TOOL}
    COMMENT "Translating UCD")

add_library (ogonek_ucd STATIC ${ucd_gen_SRC})
