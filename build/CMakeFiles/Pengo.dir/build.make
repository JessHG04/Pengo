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
CMAKE_SOURCE_DIR = /home/jessica/Desktop/Pengo2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jessica/Desktop/Pengo2/build

# Include any dependencies generated for this target.
include CMakeFiles/Pengo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Pengo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Pengo.dir/flags.make

CMakeFiles/Pengo.dir/main.cpp.o: CMakeFiles/Pengo.dir/flags.make
CMakeFiles/Pengo.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jessica/Desktop/Pengo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Pengo.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Pengo.dir/main.cpp.o -c /home/jessica/Desktop/Pengo2/main.cpp

CMakeFiles/Pengo.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Pengo.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jessica/Desktop/Pengo2/main.cpp > CMakeFiles/Pengo.dir/main.cpp.i

CMakeFiles/Pengo.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Pengo.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jessica/Desktop/Pengo2/main.cpp -o CMakeFiles/Pengo.dir/main.cpp.s

CMakeFiles/Pengo.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Pengo.dir/main.cpp.o.requires

CMakeFiles/Pengo.dir/main.cpp.o.provides: CMakeFiles/Pengo.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Pengo.dir/build.make CMakeFiles/Pengo.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Pengo.dir/main.cpp.o.provides

CMakeFiles/Pengo.dir/main.cpp.o.provides.build: CMakeFiles/Pengo.dir/main.cpp.o


# Object files for target Pengo
Pengo_OBJECTS = \
"CMakeFiles/Pengo.dir/main.cpp.o"

# External object files for target Pengo
Pengo_EXTERNAL_OBJECTS =

Pengo: CMakeFiles/Pengo.dir/main.cpp.o
Pengo: CMakeFiles/Pengo.dir/build.make
Pengo: liblibModulos.a
Pengo: /usr/lib/x86_64-linux-gnu/libsfml-system.so
Pengo: /usr/lib/x86_64-linux-gnu/libsfml-window.so
Pengo: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so
Pengo: /usr/lib/x86_64-linux-gnu/libsfml-network.so
Pengo: /usr/lib/x86_64-linux-gnu/libsfml-audio.so
Pengo: CMakeFiles/Pengo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jessica/Desktop/Pengo2/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Pengo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Pengo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Pengo.dir/build: Pengo

.PHONY : CMakeFiles/Pengo.dir/build

CMakeFiles/Pengo.dir/requires: CMakeFiles/Pengo.dir/main.cpp.o.requires

.PHONY : CMakeFiles/Pengo.dir/requires

CMakeFiles/Pengo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Pengo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Pengo.dir/clean

CMakeFiles/Pengo.dir/depend:
	cd /home/jessica/Desktop/Pengo2/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jessica/Desktop/Pengo2 /home/jessica/Desktop/Pengo2 /home/jessica/Desktop/Pengo2/build /home/jessica/Desktop/Pengo2/build /home/jessica/Desktop/Pengo2/build/CMakeFiles/Pengo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Pengo.dir/depend

