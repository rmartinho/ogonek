cmake_minimum_required (VERSION 3.2)

add_library (Catch INTERFACE)
target_include_directories (Catch SYSTEM INTERFACE ${PROJECT_SOURCE_DIR}/deps/catch/single_include)
