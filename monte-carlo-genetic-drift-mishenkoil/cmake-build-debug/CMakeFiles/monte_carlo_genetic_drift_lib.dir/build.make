# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /opt/clion-2018.2.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /opt/clion-2018.2.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/monte_carlo_genetic_drift_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/monte_carlo_genetic_drift_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/monte_carlo_genetic_drift_lib.dir/flags.make

CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o: CMakeFiles/monte_carlo_genetic_drift_lib.dir/flags.make
CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o: ../src/utils.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o -c /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/src/utils.cpp

CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/src/utils.cpp > CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.i

CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/src/utils.cpp -o CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.s

# Object files for target monte_carlo_genetic_drift_lib
monte_carlo_genetic_drift_lib_OBJECTS = \
"CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o"

# External object files for target monte_carlo_genetic_drift_lib
monte_carlo_genetic_drift_lib_EXTERNAL_OBJECTS =

libmonte_carlo_genetic_drift_lib.a: CMakeFiles/monte_carlo_genetic_drift_lib.dir/src/utils.cpp.o
libmonte_carlo_genetic_drift_lib.a: CMakeFiles/monte_carlo_genetic_drift_lib.dir/build.make
libmonte_carlo_genetic_drift_lib.a: CMakeFiles/monte_carlo_genetic_drift_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libmonte_carlo_genetic_drift_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/monte_carlo_genetic_drift_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/monte_carlo_genetic_drift_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/monte_carlo_genetic_drift_lib.dir/build: libmonte_carlo_genetic_drift_lib.a

.PHONY : CMakeFiles/monte_carlo_genetic_drift_lib.dir/build

CMakeFiles/monte_carlo_genetic_drift_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/monte_carlo_genetic_drift_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/monte_carlo_genetic_drift_lib.dir/clean

CMakeFiles/monte_carlo_genetic_drift_lib.dir/depend:
	cd /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug /home/mishenkoil/Desktop/cpp-hw/monte-carlo-genetic-drift-mishenkoil/cmake-build-debug/CMakeFiles/monte_carlo_genetic_drift_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/monte_carlo_genetic_drift_lib.dir/depend

