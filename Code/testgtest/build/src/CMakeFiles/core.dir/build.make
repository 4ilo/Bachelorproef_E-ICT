# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/olivier/Documents/School/Bachelorproef/Code/testgtest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build

# Include any dependencies generated for this target.
include src/CMakeFiles/core.dir/depend.make

# Include the progress variables for this target.
include src/CMakeFiles/core.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/core.dir/flags.make

src/CMakeFiles/core.dir/main.cpp.o: src/CMakeFiles/core.dir/flags.make
src/CMakeFiles/core.dir/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/core.dir/main.cpp.o"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/core.dir/main.cpp.o -c /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/main.cpp

src/CMakeFiles/core.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/core.dir/main.cpp.i"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/main.cpp > CMakeFiles/core.dir/main.cpp.i

src/CMakeFiles/core.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/core.dir/main.cpp.s"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/main.cpp -o CMakeFiles/core.dir/main.cpp.s

src/CMakeFiles/core.dir/main.cpp.o.requires:

.PHONY : src/CMakeFiles/core.dir/main.cpp.o.requires

src/CMakeFiles/core.dir/main.cpp.o.provides: src/CMakeFiles/core.dir/main.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/core.dir/build.make src/CMakeFiles/core.dir/main.cpp.o.provides.build
.PHONY : src/CMakeFiles/core.dir/main.cpp.o.provides

src/CMakeFiles/core.dir/main.cpp.o.provides.build: src/CMakeFiles/core.dir/main.cpp.o


src/CMakeFiles/core.dir/file.cpp.o: src/CMakeFiles/core.dir/flags.make
src/CMakeFiles/core.dir/file.cpp.o: ../src/file.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/core.dir/file.cpp.o"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/core.dir/file.cpp.o -c /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/file.cpp

src/CMakeFiles/core.dir/file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/core.dir/file.cpp.i"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/file.cpp > CMakeFiles/core.dir/file.cpp.i

src/CMakeFiles/core.dir/file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/core.dir/file.cpp.s"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src/file.cpp -o CMakeFiles/core.dir/file.cpp.s

src/CMakeFiles/core.dir/file.cpp.o.requires:

.PHONY : src/CMakeFiles/core.dir/file.cpp.o.requires

src/CMakeFiles/core.dir/file.cpp.o.provides: src/CMakeFiles/core.dir/file.cpp.o.requires
	$(MAKE) -f src/CMakeFiles/core.dir/build.make src/CMakeFiles/core.dir/file.cpp.o.provides.build
.PHONY : src/CMakeFiles/core.dir/file.cpp.o.provides

src/CMakeFiles/core.dir/file.cpp.o.provides.build: src/CMakeFiles/core.dir/file.cpp.o


# Object files for target core
core_OBJECTS = \
"CMakeFiles/core.dir/main.cpp.o" \
"CMakeFiles/core.dir/file.cpp.o"

# External object files for target core
core_EXTERNAL_OBJECTS =

src/libcore.a: src/CMakeFiles/core.dir/main.cpp.o
src/libcore.a: src/CMakeFiles/core.dir/file.cpp.o
src/libcore.a: src/CMakeFiles/core.dir/build.make
src/libcore.a: src/CMakeFiles/core.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libcore.a"
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && $(CMAKE_COMMAND) -P CMakeFiles/core.dir/cmake_clean_target.cmake
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/core.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/core.dir/build: src/libcore.a

.PHONY : src/CMakeFiles/core.dir/build

src/CMakeFiles/core.dir/requires: src/CMakeFiles/core.dir/main.cpp.o.requires
src/CMakeFiles/core.dir/requires: src/CMakeFiles/core.dir/file.cpp.o.requires

.PHONY : src/CMakeFiles/core.dir/requires

src/CMakeFiles/core.dir/clean:
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src && $(CMAKE_COMMAND) -P CMakeFiles/core.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/core.dir/clean

src/CMakeFiles/core.dir/depend:
	cd /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/olivier/Documents/School/Bachelorproef/Code/testgtest /home/olivier/Documents/School/Bachelorproef/Code/testgtest/src /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src /home/olivier/Documents/School/Bachelorproef/Code/testgtest/build/src/CMakeFiles/core.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/core.dir/depend

