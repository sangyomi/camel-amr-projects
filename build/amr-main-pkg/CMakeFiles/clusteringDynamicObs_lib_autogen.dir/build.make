# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_SOURCE_DIR = /home/percy/camel-amr-projects/src/amr-main-pkg

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/percy/camel-amr-projects/build/amr-main-pkg

# Utility rule file for clusteringDynamicObs_lib_autogen.

# Include any custom commands dependencies for this target.
include CMakeFiles/clusteringDynamicObs_lib_autogen.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/clusteringDynamicObs_lib_autogen.dir/progress.make

CMakeFiles/clusteringDynamicObs_lib_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --blue --bold --progress-dir=/home/percy/camel-amr-projects/build/amr-main-pkg/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target clusteringDynamicObs_lib"
	/usr/local/bin/cmake -E cmake_autogen /home/percy/camel-amr-projects/build/amr-main-pkg/CMakeFiles/clusteringDynamicObs_lib_autogen.dir/AutogenInfo.json ""

clusteringDynamicObs_lib_autogen: CMakeFiles/clusteringDynamicObs_lib_autogen
clusteringDynamicObs_lib_autogen: CMakeFiles/clusteringDynamicObs_lib_autogen.dir/build.make
.PHONY : clusteringDynamicObs_lib_autogen

# Rule to build all files generated by this target.
CMakeFiles/clusteringDynamicObs_lib_autogen.dir/build: clusteringDynamicObs_lib_autogen
.PHONY : CMakeFiles/clusteringDynamicObs_lib_autogen.dir/build

CMakeFiles/clusteringDynamicObs_lib_autogen.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/clusteringDynamicObs_lib_autogen.dir/cmake_clean.cmake
.PHONY : CMakeFiles/clusteringDynamicObs_lib_autogen.dir/clean

CMakeFiles/clusteringDynamicObs_lib_autogen.dir/depend:
	cd /home/percy/camel-amr-projects/build/amr-main-pkg && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/percy/camel-amr-projects/src/amr-main-pkg /home/percy/camel-amr-projects/src/amr-main-pkg /home/percy/camel-amr-projects/build/amr-main-pkg /home/percy/camel-amr-projects/build/amr-main-pkg /home/percy/camel-amr-projects/build/amr-main-pkg/CMakeFiles/clusteringDynamicObs_lib_autogen.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/clusteringDynamicObs_lib_autogen.dir/depend

