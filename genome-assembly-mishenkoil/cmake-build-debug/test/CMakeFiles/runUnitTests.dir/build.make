# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/mishenkoil/snap/clion-2019.3.5/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/mishenkoil/snap/clion-2019.3.5/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug

# Include any dependencies generated for this target.
include test/CMakeFiles/runUnitTests.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/runUnitTests.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/runUnitTests.dir/flags.make

test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o: test/CMakeFiles/runUnitTests.dir/flags.make
test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o: ../test/src/genome_tests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o"
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o -c /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/test/src/genome_tests.cpp

test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.i"
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/test/src/genome_tests.cpp > CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.i

test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.s"
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/test/src/genome_tests.cpp -o CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.s

# Object files for target runUnitTests
runUnitTests_OBJECTS = \
"CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o"

# External object files for target runUnitTests
runUnitTests_EXTERNAL_OBJECTS =

test/runUnitTests: test/CMakeFiles/runUnitTests.dir/src/genome_tests.cpp.o
test/runUnitTests: test/CMakeFiles/runUnitTests.dir/build.make
test/runUnitTests: lib/libgtestd.a
test/runUnitTests: lib/libgtest_maind.a
test/runUnitTests: libgenome_assembly_lib.a
test/runUnitTests: lib/libgtestd.a
test/runUnitTests: test/CMakeFiles/runUnitTests.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable runUnitTests"
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/runUnitTests.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/runUnitTests.dir/build: test/runUnitTests

.PHONY : test/CMakeFiles/runUnitTests.dir/build

test/CMakeFiles/runUnitTests.dir/clean:
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/runUnitTests.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/runUnitTests.dir/clean

test/CMakeFiles/runUnitTests.dir/depend:
	cd /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/test /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test /home/mishenkoil/Desktop/cpp-hw/genome-assembly-mishenkoil/cmake-build-debug/test/CMakeFiles/runUnitTests.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/runUnitTests.dir/depend
