# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/codeCpp/modernCpp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/codeCpp/modernCpp/build

# Include any dependencies generated for this target.
include src/CMakeFiles/CSmart_ptr.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/CSmart_ptr.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/CSmart_ptr.dir/flags.make

src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o: src/CMakeFiles/CSmart_ptr.dir/flags.make
src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o: ../src/CSmart_ptr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/codeCpp/modernCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o"
	cd /home/codeCpp/modernCpp/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o -c /home/codeCpp/modernCpp/src/CSmart_ptr.cpp

src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.i"
	cd /home/codeCpp/modernCpp/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/codeCpp/modernCpp/src/CSmart_ptr.cpp > CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.i

src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.s"
	cd /home/codeCpp/modernCpp/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/codeCpp/modernCpp/src/CSmart_ptr.cpp -o CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.s

# Object files for target CSmart_ptr
CSmart_ptr_OBJECTS = \
"CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o"

# External object files for target CSmart_ptr
CSmart_ptr_EXTERNAL_OBJECTS =

../bin/CSmart_ptr: src/CMakeFiles/CSmart_ptr.dir/CSmart_ptr.cpp.o
../bin/CSmart_ptr: src/CMakeFiles/CSmart_ptr.dir/build.make
../bin/CSmart_ptr: src/CMakeFiles/CSmart_ptr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/codeCpp/modernCpp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../../bin/CSmart_ptr"
	cd /home/codeCpp/modernCpp/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/CSmart_ptr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/CSmart_ptr.dir/build: ../bin/CSmart_ptr

.PHONY : src/CMakeFiles/CSmart_ptr.dir/build

src/CMakeFiles/CSmart_ptr.dir/clean:
	cd /home/codeCpp/modernCpp/build/src && $(CMAKE_COMMAND) -P CMakeFiles/CSmart_ptr.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/CSmart_ptr.dir/clean

src/CMakeFiles/CSmart_ptr.dir/depend:
	cd /home/codeCpp/modernCpp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/codeCpp/modernCpp /home/codeCpp/modernCpp/src /home/codeCpp/modernCpp/build /home/codeCpp/modernCpp/build/src /home/codeCpp/modernCpp/build/src/CMakeFiles/CSmart_ptr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/CSmart_ptr.dir/depend

