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
CMAKE_SOURCE_DIR = /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/second-chance.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/second-chance.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/second-chance.dir/flags.make

CMakeFiles/second-chance.dir/src/main.cpp.o: CMakeFiles/second-chance.dir/flags.make
CMakeFiles/second-chance.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/second-chance.dir/src/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/second-chance.dir/src/main.cpp.o -c /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/src/main.cpp

CMakeFiles/second-chance.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/second-chance.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/src/main.cpp > CMakeFiles/second-chance.dir/src/main.cpp.i

CMakeFiles/second-chance.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/second-chance.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/src/main.cpp -o CMakeFiles/second-chance.dir/src/main.cpp.s

# Object files for target second-chance
second__chance_OBJECTS = \
"CMakeFiles/second-chance.dir/src/main.cpp.o"

# External object files for target second-chance
second__chance_EXTERNAL_OBJECTS =

second-chance: CMakeFiles/second-chance.dir/src/main.cpp.o
second-chance: CMakeFiles/second-chance.dir/build.make
second-chance: libsecond_chance_multi_type_lib.a
second-chance: CMakeFiles/second-chance.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable second-chance"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/second-chance.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/second-chance.dir/build: second-chance

.PHONY : CMakeFiles/second-chance.dir/build

CMakeFiles/second-chance.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/second-chance.dir/cmake_clean.cmake
.PHONY : CMakeFiles/second-chance.dir/clean

CMakeFiles/second-chance.dir/depend:
	cd /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug /home/mishenkoil/Desktop/cpp-hw/second-chance-multi-type-mishenkoil/cmake-build-debug/CMakeFiles/second-chance.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/second-chance.dir/depend

