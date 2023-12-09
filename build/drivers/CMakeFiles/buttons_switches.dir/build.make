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
include drivers/CMakeFiles/buttons_switches.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include drivers/CMakeFiles/buttons_switches.dir/compiler_depend.make

# Include the progress variables for this target.
include drivers/CMakeFiles/buttons_switches.dir/progress.make

# Include the compile flags for this target's objects.
include drivers/CMakeFiles/buttons_switches.dir/flags.make

drivers/CMakeFiles/buttons_switches.dir/buttons.c.o: drivers/CMakeFiles/buttons_switches.dir/flags.make
drivers/CMakeFiles/buttons_switches.dir/buttons.c.o: ../drivers/buttons.c
drivers/CMakeFiles/buttons_switches.dir/buttons.c.o: drivers/CMakeFiles/buttons_switches.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object drivers/CMakeFiles/buttons_switches.dir/buttons.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT drivers/CMakeFiles/buttons_switches.dir/buttons.c.o -MF CMakeFiles/buttons_switches.dir/buttons.c.o.d -o CMakeFiles/buttons_switches.dir/buttons.c.o -c /auto/fsb/ryan9801/ecen330/drivers/buttons.c

drivers/CMakeFiles/buttons_switches.dir/buttons.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/buttons_switches.dir/buttons.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/drivers/buttons.c > CMakeFiles/buttons_switches.dir/buttons.c.i

drivers/CMakeFiles/buttons_switches.dir/buttons.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/buttons_switches.dir/buttons.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/drivers/buttons.c -o CMakeFiles/buttons_switches.dir/buttons.c.s

drivers/CMakeFiles/buttons_switches.dir/switches.c.o: drivers/CMakeFiles/buttons_switches.dir/flags.make
drivers/CMakeFiles/buttons_switches.dir/switches.c.o: ../drivers/switches.c
drivers/CMakeFiles/buttons_switches.dir/switches.c.o: drivers/CMakeFiles/buttons_switches.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object drivers/CMakeFiles/buttons_switches.dir/switches.c.o"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT drivers/CMakeFiles/buttons_switches.dir/switches.c.o -MF CMakeFiles/buttons_switches.dir/switches.c.o.d -o CMakeFiles/buttons_switches.dir/switches.c.o -c /auto/fsb/ryan9801/ecen330/drivers/switches.c

drivers/CMakeFiles/buttons_switches.dir/switches.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/buttons_switches.dir/switches.c.i"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /auto/fsb/ryan9801/ecen330/drivers/switches.c > CMakeFiles/buttons_switches.dir/switches.c.i

drivers/CMakeFiles/buttons_switches.dir/switches.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/buttons_switches.dir/switches.c.s"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && arm-none-eabi-gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /auto/fsb/ryan9801/ecen330/drivers/switches.c -o CMakeFiles/buttons_switches.dir/switches.c.s

# Object files for target buttons_switches
buttons_switches_OBJECTS = \
"CMakeFiles/buttons_switches.dir/buttons.c.o" \
"CMakeFiles/buttons_switches.dir/switches.c.o"

# External object files for target buttons_switches
buttons_switches_EXTERNAL_OBJECTS =

drivers/libbuttons_switches.a: drivers/CMakeFiles/buttons_switches.dir/buttons.c.o
drivers/libbuttons_switches.a: drivers/CMakeFiles/buttons_switches.dir/switches.c.o
drivers/libbuttons_switches.a: drivers/CMakeFiles/buttons_switches.dir/build.make
drivers/libbuttons_switches.a: drivers/CMakeFiles/buttons_switches.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/auto/fsb/ryan9801/ecen330/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking C static library libbuttons_switches.a"
	cd /auto/fsb/ryan9801/ecen330/build/drivers && $(CMAKE_COMMAND) -P CMakeFiles/buttons_switches.dir/cmake_clean_target.cmake
	cd /auto/fsb/ryan9801/ecen330/build/drivers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/buttons_switches.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drivers/CMakeFiles/buttons_switches.dir/build: drivers/libbuttons_switches.a
.PHONY : drivers/CMakeFiles/buttons_switches.dir/build

drivers/CMakeFiles/buttons_switches.dir/clean:
	cd /auto/fsb/ryan9801/ecen330/build/drivers && $(CMAKE_COMMAND) -P CMakeFiles/buttons_switches.dir/cmake_clean.cmake
.PHONY : drivers/CMakeFiles/buttons_switches.dir/clean

drivers/CMakeFiles/buttons_switches.dir/depend:
	cd /auto/fsb/ryan9801/ecen330/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /auto/fsb/ryan9801/ecen330 /auto/fsb/ryan9801/ecen330/drivers /auto/fsb/ryan9801/ecen330/build /auto/fsb/ryan9801/ecen330/build/drivers /auto/fsb/ryan9801/ecen330/build/drivers/CMakeFiles/buttons_switches.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : drivers/CMakeFiles/buttons_switches.dir/depend

