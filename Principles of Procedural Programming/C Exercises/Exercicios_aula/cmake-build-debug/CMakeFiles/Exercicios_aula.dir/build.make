# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /cygdrive/c/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe

# The command to remove a file.
RM = /cygdrive/c/.CLion2019.3/system/cygwin_cmake/bin/cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /cygdrive/c/ProgramasPPP/Exercicios_aula

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Exercicios_aula.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Exercicios_aula.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Exercicios_aula.dir/flags.make

CMakeFiles/Exercicios_aula.dir/main.c.o: CMakeFiles/Exercicios_aula.dir/flags.make
CMakeFiles/Exercicios_aula.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Exercicios_aula.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Exercicios_aula.dir/main.c.o   -c /cygdrive/c/ProgramasPPP/Exercicios_aula/main.c

CMakeFiles/Exercicios_aula.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Exercicios_aula.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /cygdrive/c/ProgramasPPP/Exercicios_aula/main.c > CMakeFiles/Exercicios_aula.dir/main.c.i

CMakeFiles/Exercicios_aula.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Exercicios_aula.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /cygdrive/c/ProgramasPPP/Exercicios_aula/main.c -o CMakeFiles/Exercicios_aula.dir/main.c.s

# Object files for target Exercicios_aula
Exercicios_aula_OBJECTS = \
"CMakeFiles/Exercicios_aula.dir/main.c.o"

# External object files for target Exercicios_aula
Exercicios_aula_EXTERNAL_OBJECTS =

Exercicios_aula.exe: CMakeFiles/Exercicios_aula.dir/main.c.o
Exercicios_aula.exe: CMakeFiles/Exercicios_aula.dir/build.make
Exercicios_aula.exe: CMakeFiles/Exercicios_aula.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Exercicios_aula.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Exercicios_aula.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Exercicios_aula.dir/build: Exercicios_aula.exe

.PHONY : CMakeFiles/Exercicios_aula.dir/build

CMakeFiles/Exercicios_aula.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Exercicios_aula.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Exercicios_aula.dir/clean

CMakeFiles/Exercicios_aula.dir/depend:
	cd /cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /cygdrive/c/ProgramasPPP/Exercicios_aula /cygdrive/c/ProgramasPPP/Exercicios_aula /cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug /cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug /cygdrive/c/ProgramasPPP/Exercicios_aula/cmake-build-debug/CMakeFiles/Exercicios_aula.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Exercicios_aula.dir/depend

