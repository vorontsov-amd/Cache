# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/amadey/Документы/Projects/Cache

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/amadey/Документы/Projects/Cache/build

# Include any dependencies generated for this target.
include lfu_cache/CMakeFiles/lfu.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lfu_cache/CMakeFiles/lfu.dir/compiler_depend.make

# Include the progress variables for this target.
include lfu_cache/CMakeFiles/lfu.dir/progress.make

# Include the compile flags for this target's objects.
include lfu_cache/CMakeFiles/lfu.dir/flags.make

lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o: lfu_cache/CMakeFiles/lfu.dir/flags.make
lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o: /home/amadey/Документы/Projects/Cache/lfu_cache/src/main.cpp
lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o: lfu_cache/CMakeFiles/lfu.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/amadey/Документы/Projects/Cache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o"
	cd /home/amadey/Документы/Projects/Cache/build/lfu_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o -MF CMakeFiles/lfu.dir/src/main.cpp.o.d -o CMakeFiles/lfu.dir/src/main.cpp.o -c /home/amadey/Документы/Projects/Cache/lfu_cache/src/main.cpp

lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lfu.dir/src/main.cpp.i"
	cd /home/amadey/Документы/Projects/Cache/build/lfu_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/amadey/Документы/Projects/Cache/lfu_cache/src/main.cpp > CMakeFiles/lfu.dir/src/main.cpp.i

lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lfu.dir/src/main.cpp.s"
	cd /home/amadey/Документы/Projects/Cache/build/lfu_cache && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/amadey/Документы/Projects/Cache/lfu_cache/src/main.cpp -o CMakeFiles/lfu.dir/src/main.cpp.s

# Object files for target lfu
lfu_OBJECTS = \
"CMakeFiles/lfu.dir/src/main.cpp.o"

# External object files for target lfu
lfu_EXTERNAL_OBJECTS =

bin/lfu: lfu_cache/CMakeFiles/lfu.dir/src/main.cpp.o
bin/lfu: lfu_cache/CMakeFiles/lfu.dir/build.make
bin/lfu: lfu_cache/CMakeFiles/lfu.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/amadey/Документы/Projects/Cache/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ../bin/lfu"
	cd /home/amadey/Документы/Projects/Cache/build/lfu_cache && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lfu.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lfu_cache/CMakeFiles/lfu.dir/build: bin/lfu
.PHONY : lfu_cache/CMakeFiles/lfu.dir/build

lfu_cache/CMakeFiles/lfu.dir/clean:
	cd /home/amadey/Документы/Projects/Cache/build/lfu_cache && $(CMAKE_COMMAND) -P CMakeFiles/lfu.dir/cmake_clean.cmake
.PHONY : lfu_cache/CMakeFiles/lfu.dir/clean

lfu_cache/CMakeFiles/lfu.dir/depend:
	cd /home/amadey/Документы/Projects/Cache/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/amadey/Документы/Projects/Cache /home/amadey/Документы/Projects/Cache/lfu_cache /home/amadey/Документы/Projects/Cache/build /home/amadey/Документы/Projects/Cache/build/lfu_cache /home/amadey/Документы/Projects/Cache/build/lfu_cache/CMakeFiles/lfu.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lfu_cache/CMakeFiles/lfu.dir/depend

