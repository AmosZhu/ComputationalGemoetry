# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /software/clion-2019.1.3/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /software/clion-2019.1.3/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/hgfs/Linux/ComputationalGemoetry

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/PA1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/PA1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/PA1.dir/flags.make

CMakeFiles/PA1.dir/convexhull.cpp.o: CMakeFiles/PA1.dir/flags.make
CMakeFiles/PA1.dir/convexhull.cpp.o: ../convexhull.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/PA1.dir/convexhull.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/PA1.dir/convexhull.cpp.o -c /mnt/hgfs/Linux/ComputationalGemoetry/convexhull.cpp

CMakeFiles/PA1.dir/convexhull.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/PA1.dir/convexhull.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/hgfs/Linux/ComputationalGemoetry/convexhull.cpp > CMakeFiles/PA1.dir/convexhull.cpp.i

CMakeFiles/PA1.dir/convexhull.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/PA1.dir/convexhull.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/hgfs/Linux/ComputationalGemoetry/convexhull.cpp -o CMakeFiles/PA1.dir/convexhull.cpp.s

# Object files for target PA1
PA1_OBJECTS = \
"CMakeFiles/PA1.dir/convexhull.cpp.o"

# External object files for target PA1
PA1_EXTERNAL_OBJECTS =

PA1: CMakeFiles/PA1.dir/convexhull.cpp.o
PA1: CMakeFiles/PA1.dir/build.make
PA1: CMakeFiles/PA1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable PA1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/PA1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/PA1.dir/build: PA1

.PHONY : CMakeFiles/PA1.dir/build

CMakeFiles/PA1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/PA1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/PA1.dir/clean

CMakeFiles/PA1.dir/depend:
	cd /mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/hgfs/Linux/ComputationalGemoetry /mnt/hgfs/Linux/ComputationalGemoetry /mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug /mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug /mnt/hgfs/Linux/ComputationalGemoetry/cmake-build-debug/CMakeFiles/PA1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/PA1.dir/depend

