# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/cmake/1156/bin/cmake

# The command to remove a file.
RM = /snap/cmake/1156/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/stelios/Desktop/PROJECT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/stelios/Desktop/PROJECT

# Include any dependencies generated for this target.
include include/CMakeFiles/convex_hull_functions.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include include/CMakeFiles/convex_hull_functions.dir/compiler_depend.make

# Include the progress variables for this target.
include include/CMakeFiles/convex_hull_functions.dir/progress.make

# Include the compile flags for this target's objects.
include include/CMakeFiles/convex_hull_functions.dir/flags.make

include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o: include/CMakeFiles/convex_hull_functions.dir/flags.make
include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o: include/convex_hull_functions.cpp
include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o: include/CMakeFiles/convex_hull_functions.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/stelios/Desktop/PROJECT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o"
	cd /home/stelios/Desktop/PROJECT/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o -MF CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o.d -o CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o -c /home/stelios/Desktop/PROJECT/include/convex_hull_functions.cpp

include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.i"
	cd /home/stelios/Desktop/PROJECT/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/stelios/Desktop/PROJECT/include/convex_hull_functions.cpp > CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.i

include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.s"
	cd /home/stelios/Desktop/PROJECT/include && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/stelios/Desktop/PROJECT/include/convex_hull_functions.cpp -o CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.s

# Object files for target convex_hull_functions
convex_hull_functions_OBJECTS = \
"CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o"

# External object files for target convex_hull_functions
convex_hull_functions_EXTERNAL_OBJECTS =

include/libconvex_hull_functions.a: include/CMakeFiles/convex_hull_functions.dir/convex_hull_functions.cpp.o
include/libconvex_hull_functions.a: include/CMakeFiles/convex_hull_functions.dir/build.make
include/libconvex_hull_functions.a: include/CMakeFiles/convex_hull_functions.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/stelios/Desktop/PROJECT/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libconvex_hull_functions.a"
	cd /home/stelios/Desktop/PROJECT/include && $(CMAKE_COMMAND) -P CMakeFiles/convex_hull_functions.dir/cmake_clean_target.cmake
	cd /home/stelios/Desktop/PROJECT/include && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/convex_hull_functions.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
include/CMakeFiles/convex_hull_functions.dir/build: include/libconvex_hull_functions.a
.PHONY : include/CMakeFiles/convex_hull_functions.dir/build

include/CMakeFiles/convex_hull_functions.dir/clean:
	cd /home/stelios/Desktop/PROJECT/include && $(CMAKE_COMMAND) -P CMakeFiles/convex_hull_functions.dir/cmake_clean.cmake
.PHONY : include/CMakeFiles/convex_hull_functions.dir/clean

include/CMakeFiles/convex_hull_functions.dir/depend:
	cd /home/stelios/Desktop/PROJECT && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/stelios/Desktop/PROJECT /home/stelios/Desktop/PROJECT/include /home/stelios/Desktop/PROJECT /home/stelios/Desktop/PROJECT/include /home/stelios/Desktop/PROJECT/include/CMakeFiles/convex_hull_functions.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : include/CMakeFiles/convex_hull_functions.dir/depend
