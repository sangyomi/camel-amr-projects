# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_SOURCE_DIR = /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg

# Include any dependencies generated for this target.
include CMakeFiles/visualize_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/visualize_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/visualize_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/visualize_lib.dir/flags.make

CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o: CMakeFiles/visualize_lib.dir/flags.make
CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o: visualize_lib_autogen/mocs_compilation.cpp
CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o: CMakeFiles/visualize_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o -MF CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o -c /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/visualize_lib_autogen/mocs_compilation.cpp

CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/visualize_lib_autogen/mocs_compilation.cpp > CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.i

CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/visualize_lib_autogen/mocs_compilation.cpp -o CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.s

CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o: CMakeFiles/visualize_lib.dir/flags.make
CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o: /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg/src/Visualize/Map_In_Out.cpp
CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o: CMakeFiles/visualize_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o -MF CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o.d -o CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o -c /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg/src/Visualize/Map_In_Out.cpp

CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg/src/Visualize/Map_In_Out.cpp > CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.i

CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg/src/Visualize/Map_In_Out.cpp -o CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.s

# Object files for target visualize_lib
visualize_lib_OBJECTS = \
"CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o"

# External object files for target visualize_lib
visualize_lib_EXTERNAL_OBJECTS =

libvisualize_lib.a: CMakeFiles/visualize_lib.dir/visualize_lib_autogen/mocs_compilation.cpp.o
libvisualize_lib.a: CMakeFiles/visualize_lib.dir/src/Visualize/Map_In_Out.cpp.o
libvisualize_lib.a: CMakeFiles/visualize_lib.dir/build.make
libvisualize_lib.a: CMakeFiles/visualize_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libvisualize_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/visualize_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/visualize_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/visualize_lib.dir/build: libvisualize_lib.a
.PHONY : CMakeFiles/visualize_lib.dir/build

CMakeFiles/visualize_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/visualize_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/visualize_lib.dir/clean

CMakeFiles/visualize_lib.dir/depend:
	cd /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg /home/sangjun/camel-amr-projects-UI/src/amr-main-pkg /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg /home/sangjun/camel-amr-projects-UI/build/amr-main-pkg/CMakeFiles/visualize_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/visualize_lib.dir/depend

