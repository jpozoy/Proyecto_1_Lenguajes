# CMake generated Testfile for 
# Source directory: /home/jeff/lenguajes/proyecto-1/cJSON
# Build directory: /home/jeff/lenguajes/proyecto-1/build/cJSON
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(cJSON_test "/home/jeff/lenguajes/proyecto-1/build/cJSON/cJSON_test")
set_tests_properties(cJSON_test PROPERTIES  _BACKTRACE_TRIPLES "/home/jeff/lenguajes/proyecto-1/cJSON/CMakeLists.txt;248;add_test;/home/jeff/lenguajes/proyecto-1/cJSON/CMakeLists.txt;0;")
subdirs("tests")
subdirs("fuzzing")
