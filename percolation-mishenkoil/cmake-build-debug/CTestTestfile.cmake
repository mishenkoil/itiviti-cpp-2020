# CMake generated Testfile for 
# Source directory: /home/mishenkoil/Desktop/cpp-hw/percolation-mishenkoil
# Build directory: /home/mishenkoil/Desktop/cpp-hw/percolation-mishenkoil/cmake-build-debug
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "/home/mishenkoil/Desktop/cpp-hw/percolation-mishenkoil/cmake-build-debug/test/runUnitTests")
set_tests_properties(tests PROPERTIES  _BACKTRACE_TRIPLES "/home/mishenkoil/Desktop/cpp-hw/percolation-mishenkoil/CMakeLists.txt;42;add_test;/home/mishenkoil/Desktop/cpp-hw/percolation-mishenkoil/CMakeLists.txt;0;")
subdirs("googletest")
subdirs("test")
