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
CMAKE_SOURCE_DIR = /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/proc_hier.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/proc_hier.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/proc_hier.dir/flags.make

CMakeFiles/proc_hier.dir/proc_hier.c.o: CMakeFiles/proc_hier.dir/flags.make
CMakeFiles/proc_hier.dir/proc_hier.c.o: ../proc_hier.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/proc_hier.dir/proc_hier.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/proc_hier.dir/proc_hier.c.o   -c /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/proc_hier.c

CMakeFiles/proc_hier.dir/proc_hier.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/proc_hier.dir/proc_hier.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/proc_hier.c > CMakeFiles/proc_hier.dir/proc_hier.c.i

CMakeFiles/proc_hier.dir/proc_hier.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/proc_hier.dir/proc_hier.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/proc_hier.c -o CMakeFiles/proc_hier.dir/proc_hier.c.s

# Object files for target proc_hier
proc_hier_OBJECTS = \
"CMakeFiles/proc_hier.dir/proc_hier.c.o"

# External object files for target proc_hier
proc_hier_EXTERNAL_OBJECTS =

bin/proc_hier: CMakeFiles/proc_hier.dir/proc_hier.c.o
bin/proc_hier: CMakeFiles/proc_hier.dir/build.make
bin/proc_hier: CMakeFiles/proc_hier.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable bin/proc_hier"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/proc_hier.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/proc_hier.dir/build: bin/proc_hier

.PHONY : CMakeFiles/proc_hier.dir/build

CMakeFiles/proc_hier.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/proc_hier.dir/cmake_clean.cmake
.PHONY : CMakeFiles/proc_hier.dir/clean

CMakeFiles/proc_hier.dir/depend:
	cd /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug /home/christophervalencia/Desktop/comp362/ValenciaChristopherLab03/proc_hier/cmake-build-debug/CMakeFiles/proc_hier.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/proc_hier.dir/depend

