# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/dongju/camel-amr-projects/src/amr-main-pkg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dongju/camel-amr-projects/build/amr-main-pkg

# Include any dependencies generated for this target.
include CMakeFiles/obsDetection_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/obsDetection_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/obsDetection_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/obsDetection_lib.dir/flags.make

CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o: CMakeFiles/obsDetection_lib.dir/flags.make
CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o: obsDetection_lib_autogen/mocs_compilation.cpp
CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o: CMakeFiles/obsDetection_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongju/camel-amr-projects/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o -MF CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o -c /home/dongju/camel-amr-projects/build/amr-main-pkg/obsDetection_lib_autogen/mocs_compilation.cpp

CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dongju/camel-amr-projects/build/amr-main-pkg/obsDetection_lib_autogen/mocs_compilation.cpp > CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.i

CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dongju/camel-amr-projects/build/amr-main-pkg/obsDetection_lib_autogen/mocs_compilation.cpp -o CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.s

CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o: CMakeFiles/obsDetection_lib.dir/flags.make
CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o: /home/dongju/camel-amr-projects/src/amr-main-pkg/src/ObsDetection/ObsDetection.cpp
CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o: CMakeFiles/obsDetection_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dongju/camel-amr-projects/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o -MF CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o.d -o CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o -c /home/dongju/camel-amr-projects/src/amr-main-pkg/src/ObsDetection/ObsDetection.cpp

CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dongju/camel-amr-projects/src/amr-main-pkg/src/ObsDetection/ObsDetection.cpp > CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.i

CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dongju/camel-amr-projects/src/amr-main-pkg/src/ObsDetection/ObsDetection.cpp -o CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.s

# Object files for target obsDetection_lib
obsDetection_lib_OBJECTS = \
"CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o"

# External object files for target obsDetection_lib
obsDetection_lib_EXTERNAL_OBJECTS =

libobsDetection_lib.a: CMakeFiles/obsDetection_lib.dir/obsDetection_lib_autogen/mocs_compilation.cpp.o
libobsDetection_lib.a: CMakeFiles/obsDetection_lib.dir/src/ObsDetection/ObsDetection.cpp.o
libobsDetection_lib.a: CMakeFiles/obsDetection_lib.dir/build.make
libobsDetection_lib.a: CMakeFiles/obsDetection_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dongju/camel-amr-projects/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libobsDetection_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/obsDetection_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/obsDetection_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/obsDetection_lib.dir/build: libobsDetection_lib.a
.PHONY : CMakeFiles/obsDetection_lib.dir/build

CMakeFiles/obsDetection_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/obsDetection_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/obsDetection_lib.dir/clean

CMakeFiles/obsDetection_lib.dir/depend:
	cd /home/dongju/camel-amr-projects/build/amr-main-pkg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dongju/camel-amr-projects/src/amr-main-pkg /home/dongju/camel-amr-projects/src/amr-main-pkg /home/dongju/camel-amr-projects/build/amr-main-pkg /home/dongju/camel-amr-projects/build/amr-main-pkg /home/dongju/camel-amr-projects/build/amr-main-pkg/CMakeFiles/obsDetection_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/obsDetection_lib.dir/depend

