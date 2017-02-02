cmake_minimum_required (VERSION 3.2)

enable_testing ()
add_test (NAME ucd_test COMMAND ucd_test)
add_test (NAME encoding_test COMMAND encoding_test)
