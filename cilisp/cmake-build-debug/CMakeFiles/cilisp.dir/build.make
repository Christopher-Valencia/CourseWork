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
CMAKE_SOURCE_DIR = /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/cilisp.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/cilisp.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cilisp.dir/flags.make

../src/bison-flex-output/parser.c: ../src/cilisp.y
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "[BISON][parser] Building parser with bison 3.5.1"
	cd /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu && /usr/bin/bison -d --verbose -o /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/parser.c src/cilisp.y

../src/bison-flex-output/parser.output: ../src/bison-flex-output/parser.c
	@$(CMAKE_COMMAND) -E touch_nocreate ../src/bison-flex-output/parser.output

../src/bison-flex-output/parser.h: ../src/bison-flex-output/parser.c
	@$(CMAKE_COMMAND) -E touch_nocreate ../src/bison-flex-output/parser.h

../src/bison-flex-output/lexer.c: ../src/cilisp.l
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "[FLEX][lexer] Building scanner with flex 2.6.4"
	cd /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu && /usr/bin/flex -o/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/lexer.c src/cilisp.l

CMakeFiles/cilisp.dir/src/cilisp.c.o: CMakeFiles/cilisp.dir/flags.make
CMakeFiles/cilisp.dir/src/cilisp.c.o: ../src/cilisp.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/cilisp.dir/src/cilisp.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cilisp.dir/src/cilisp.c.o   -c /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/cilisp.c

CMakeFiles/cilisp.dir/src/cilisp.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cilisp.dir/src/cilisp.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/cilisp.c > CMakeFiles/cilisp.dir/src/cilisp.c.i

CMakeFiles/cilisp.dir/src/cilisp.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cilisp.dir/src/cilisp.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/cilisp.c -o CMakeFiles/cilisp.dir/src/cilisp.c.s

CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o: CMakeFiles/cilisp.dir/flags.make
CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o: ../src/bison-flex-output/lexer.c
CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o: ../src/bison-flex-output/parser.h
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o   -c /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/lexer.c

CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/lexer.c > CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.i

CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/lexer.c -o CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.s

CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o: CMakeFiles/cilisp.dir/flags.make
CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o: ../src/bison-flex-output/parser.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o   -c /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/parser.c

CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/parser.c > CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.i

CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/src/bison-flex-output/parser.c -o CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.s

# Object files for target cilisp
cilisp_OBJECTS = \
"CMakeFiles/cilisp.dir/src/cilisp.c.o" \
"CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o" \
"CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o"

# External object files for target cilisp
cilisp_EXTERNAL_OBJECTS =

cilisp: CMakeFiles/cilisp.dir/src/cilisp.c.o
cilisp: CMakeFiles/cilisp.dir/src/bison-flex-output/lexer.c.o
cilisp: CMakeFiles/cilisp.dir/src/bison-flex-output/parser.c.o
cilisp: CMakeFiles/cilisp.dir/build.make
cilisp: CMakeFiles/cilisp.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable cilisp"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cilisp.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cilisp.dir/build: cilisp

.PHONY : CMakeFiles/cilisp.dir/build

CMakeFiles/cilisp.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cilisp.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cilisp.dir/clean

CMakeFiles/cilisp.dir/depend: ../src/bison-flex-output/parser.c
CMakeFiles/cilisp.dir/depend: ../src/bison-flex-output/parser.output
CMakeFiles/cilisp.dir/depend: ../src/bison-flex-output/parser.h
CMakeFiles/cilisp.dir/depend: ../src/bison-flex-output/lexer.c
	cd /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug /mnt/c/Users/Ckthulu/Documents/GitHub/cilisp-Ckthulu/cmake-build-debug/CMakeFiles/cilisp.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/cilisp.dir/depend

