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
include lab5/CMakeFiles/lab5.elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lab5/CMakeFiles/lab5.elf.dir/compiler_depend.make

# Include the progress variables for this target.
include lab5/CMakeFiles/lab5.elf.dir/progress.make

# Include the compile flags for this target's objects.
include lab5/CMakeFiles/lab5.elf.dir/flags.make

lab5/CMakeFiles/lab5.elf.dir/main.c.o: lab5/CMakeFiles/lab5.elf.dir/flags.make
lab5/CMakeFiles/lab5.elf.dir/main.c.o: ../lab5/main.c
lab5/CMakeFiles/lab5.elf.dir/main.c.o: lab5/CMakeFiles/lab5.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object lab5/CMakeFiles/lab5.elf.dir/main.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab5/CMakeFiles/lab5.elf.dir/main.c.o -MF CMakeFiles/lab5.elf.dir/main.c.o.d -o CMakeFiles/lab5.elf.dir/main.c.o -c /auto/fsb/ryan9801/ecen330/lab5/main.c

lab5/CMakeFiles/lab5.elf.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5.elf.dir/main.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab5/main.c > CMakeFiles/lab5.elf.dir/main.c.i

lab5/CMakeFiles/lab5.elf.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5.elf.dir/main.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab5/main.c -o CMakeFiles/lab5.elf.dir/main.c.s

lab5/CMakeFiles/lab5.elf.dir/minimax.c.o: lab5/CMakeFiles/lab5.elf.dir/flags.make
lab5/CMakeFiles/lab5.elf.dir/minimax.c.o: ../lab5/minimax.c
lab5/CMakeFiles/lab5.elf.dir/minimax.c.o: lab5/CMakeFiles/lab5.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object lab5/CMakeFiles/lab5.elf.dir/minimax.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab5/CMakeFiles/lab5.elf.dir/minimax.c.o -MF CMakeFiles/lab5.elf.dir/minimax.c.o.d -o CMakeFiles/lab5.elf.dir/minimax.c.o -c /auto/fsb/ryan9801/ecen330/lab5/minimax.c

lab5/CMakeFiles/lab5.elf.dir/minimax.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5.elf.dir/minimax.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab5/minimax.c > CMakeFiles/lab5.elf.dir/minimax.c.i

lab5/CMakeFiles/lab5.elf.dir/minimax.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5.elf.dir/minimax.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab5/minimax.c -o CMakeFiles/lab5.elf.dir/minimax.c.s

lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o: lab5/CMakeFiles/lab5.elf.dir/flags.make
lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o: ../lab5/ticTacToeDisplay.c
lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o: lab5/CMakeFiles/lab5.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o -MF CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o.d -o CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o -c /auto/fsb/ryan9801/ecen330/lab5/ticTacToeDisplay.c

lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab5/ticTacToeDisplay.c > CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.i

lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab5/ticTacToeDisplay.c -o CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.s

lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o: lab5/CMakeFiles/lab5.elf.dir/flags.make
lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o: ../lab5/ticTacToeControl.c
lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o: lab5/CMakeFiles/lab5.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o -MF CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o.d -o CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o -c /auto/fsb/ryan9801/ecen330/lab5/ticTacToeControl.c

lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5.elf.dir/ticTacToeControl.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab5/ticTacToeControl.c > CMakeFiles/lab5.elf.dir/ticTacToeControl.c.i

lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5.elf.dir/ticTacToeControl.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab5/ticTacToeControl.c -o CMakeFiles/lab5.elf.dir/ticTacToeControl.c.s

lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o: lab5/CMakeFiles/lab5.elf.dir/flags.make
lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o: ../lab5/testBoards.c
lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o: lab5/CMakeFiles/lab5.elf.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o -MF CMakeFiles/lab5.elf.dir/testBoards.c.o.d -o CMakeFiles/lab5.elf.dir/testBoards.c.o -c /auto/fsb/ryan9801/ecen330/lab5/testBoards.c

lab5/CMakeFiles/lab5.elf.dir/testBoards.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/lab5.elf.dir/testBoards.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/lab5/testBoards.c > CMakeFiles/lab5.elf.dir/testBoards.c.i

lab5/CMakeFiles/lab5.elf.dir/testBoards.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/lab5.elf.dir/testBoards.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/lab5/testBoards.c -o CMakeFiles/lab5.elf.dir/testBoards.c.s

# Object files for target lab5.elf
lab5_elf_OBJECTS = \
"CMakeFiles/lab5.elf.dir/main.c.o" \
"CMakeFiles/lab5.elf.dir/minimax.c.o" \
"CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o" \
"CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o" \
"CMakeFiles/lab5.elf.dir/testBoards.c.o"

# External object files for target lab5.elf
lab5_elf_EXTERNAL_OBJECTS =

lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/main.c.o
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/minimax.c.o
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/ticTacToeDisplay.c.o
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/ticTacToeControl.c.o
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/testBoards.c.o
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/build.make
lab5/lab5.elf: drivers/libintervalTimer.a
lab5/lab5.elf: drivers/libbuttons_switches.a
lab5/lab5.elf: lab5/CMakeFiles/lab5.elf.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable lab5.elf"
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab5.elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lab5/CMakeFiles/lab5.elf.dir/build: lab5/lab5.elf
.PHONY : lab5/CMakeFiles/lab5.elf.dir/build

lab5/CMakeFiles/lab5.elf.dir/clean:
	cd /auto/fsb/ryan9801/ecen330/build/lab5 && $(CMAKE_COMMAND) -P CMakeFiles/lab5.elf.dir/cmake_clean.cmake
.PHONY : lab5/CMakeFiles/lab5.elf.dir/clean

lab5/CMakeFiles/lab5.elf.dir/depend:
	cd /auto/fsb/ryan9801/ecen330/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /auto/fsb/ryan9801/ecen330 /auto/fsb/ryan9801/ecen330/lab5 /auto/fsb/ryan9801/ecen330/build /auto/fsb/ryan9801/ecen330/build/lab5 /auto/fsb/ryan9801/ecen330/build/lab5/CMakeFiles/lab5.elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lab5/CMakeFiles/lab5.elf.dir/depend

