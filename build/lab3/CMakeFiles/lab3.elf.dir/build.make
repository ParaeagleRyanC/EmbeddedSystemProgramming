# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /auto/fsb/ryan9801/ecen330

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /auto/fsb/ryan9801/ecen330/build

# Include any dependencies generated for this target.
include lab3/CMakeFiles/lab3.elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lab3/CMakeFiles/lab3.elf.dir/compiler_depend.make

# Include the progress variables for this target.
include lab3/CMakeFiles/lab3.elf.dir/progress.make

# Include the compile flags for this target's objects.
include lab3/CMakeFiles/lab3.elf.dir/flags.make

lab3/CMakeFiles/lab3.elf.dir/main.c.o: lab3/CMakeFiles/lab3.elf.dir/flags.make
lab3/CMakeFiles/lab3.elf.dir/main.c.o: ../lab3/main.c
lab3/CMakeFiles/lab3.elf.dir/main.c.o: lab3/CMakeFiles/lab3.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lab3/CMakeFiles/lab3.elf.dir/main.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab3 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab3/CMakeFiles/lab3.elf.dir/main.c.o -MF CMakeFiles/lab3.elf.dir/main.c.o.d -o CMakeFiles/lab3.elf.dir/main.c.o -c /auto/fsb/ryan9801/ecen330/lab3/main.c

lab3/CMakeFiles/lab3.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab3.elf.dir/main.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab3 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab3/main.c > CMakeFiles/lab3.elf.dir/main.c.i

lab3/CMakeFiles/lab3.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab3.elf.dir/main.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab3 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab3/main.c -o CMakeFiles/lab3.elf.dir/main.c.s

# Object files for target lab3.elf
lab3_elf_OBJECTS = \
"CMakeFiles/lab3.elf.dir/main.c.o"

# External object files for target lab3.elf
lab3_elf_EXTERNAL_OBJECTS =

lab3/lab3.elf: lab3/CMakeFiles/lab3.elf.dir/main.c.o
lab3/lab3.elf: lab3/CMakeFiles/lab3.elf.dir/build.make
lab3/lab3.elf: drivers/libintervalTimer.a
lab3/lab3.elf: drivers/libbuttons_switches.a
lab3/lab3.elf: lab3/CMakeFiles/lab3.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable lab3.elf"
	cd /auto/fsb/ryan9801/ecen330/build/lab3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab3.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lab3/CMakeFiles/lab3.elf.dir/build: lab3/lab3.elf
.PHONY : lab3/CMakeFiles/lab3.elf.dir/build

lab3/CMakeFiles/lab3.elf.dir/clean:
	cd /auto/fsb/ryan9801/ecen330/build/lab3 && $(CMAKE_COMMAND) -P CMakeFiles/lab3.elf.dir/cmake_clean.cmake
.PHONY : lab3/CMakeFiles/lab3.elf.dir/clean

lab3/CMakeFiles/lab3.elf.dir/depend:
	cd /auto/fsb/ryan9801/ecen330/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /auto/fsb/ryan9801/ecen330 /auto/fsb/ryan9801/ecen330/lab3 /auto/fsb/ryan9801/ecen330/build /auto/fsb/ryan9801/ecen330/build/lab3 /auto/fsb/ryan9801/ecen330/build/lab3/CMakeFiles/lab3.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lab3/CMakeFiles/lab3.elf.dir/depend

