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
CMAKE_SOURCE_DIR = /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/avg_server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/avg_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/avg_server.dir/flags.make

CMakeFiles/avg_server.dir/avg_POSIX_server.c.o: CMakeFiles/avg_server.dir/flags.make
CMakeFiles/avg_server.dir/avg_POSIX_server.c.o: ../avg_POSIX_server.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/avg_server.dir/avg_POSIX_server.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/avg_server.dir/avg_POSIX_server.c.o   -c /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/avg_POSIX_server.c

CMakeFiles/avg_server.dir/avg_POSIX_server.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/avg_server.dir/avg_POSIX_server.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/avg_POSIX_server.c > CMakeFiles/avg_server.dir/avg_POSIX_server.c.i

CMakeFiles/avg_server.dir/avg_POSIX_server.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/avg_server.dir/avg_POSIX_server.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/avg_POSIX_server.c -o CMakeFiles/avg_server.dir/avg_POSIX_server.c.s

# Object files for target avg_server
avg_server_OBJECTS = \
"CMakeFiles/avg_server.dir/avg_POSIX_server.c.o"

# External object files for target avg_server
avg_server_EXTERNAL_OBJECTS =

bin/avg_server: CMakeFiles/avg_server.dir/avg_POSIX_server.c.o
bin/avg_server: CMakeFiles/avg_server.dir/build.make
bin/avg_server: CMakeFiles/avg_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/avg_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/avg_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/avg_server.dir/build: bin/avg_server

.PHONY : CMakeFiles/avg_server.dir/build

CMakeFiles/avg_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/avg_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/avg_server.dir/clean

CMakeFiles/avg_server.dir/depend:
	cd /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug /home/christophervalencia/Desktop/comp362/Lab04/avg_POSIX_uni/cmake-build-debug/CMakeFiles/avg_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/avg_server.dir/depend

