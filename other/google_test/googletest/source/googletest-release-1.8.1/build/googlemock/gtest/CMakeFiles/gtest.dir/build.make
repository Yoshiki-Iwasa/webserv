# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.20.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.20.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build

# Include any dependencies generated for this target.
include googlemock/gtest/CMakeFiles/gtest.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include googlemock/gtest/CMakeFiles/gtest.dir/compiler_depend.make

# Include the progress variables for this target.
include googlemock/gtest/CMakeFiles/gtest.dir/progress.make

# Include the compile flags for this target's objects.
include googlemock/gtest/CMakeFiles/gtest.dir/flags.make

googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googlemock/gtest/CMakeFiles/gtest.dir/flags.make
googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: ../googletest/src/gtest-all.cc
googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o: googlemock/gtest/CMakeFiles/gtest.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o"
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o -MF CMakeFiles/gtest.dir/src/gtest-all.cc.o.d -o CMakeFiles/gtest.dir/src/gtest-all.cc.o -c /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/googletest/src/gtest-all.cc

googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest.dir/src/gtest-all.cc.i"
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/googletest/src/gtest-all.cc > CMakeFiles/gtest.dir/src/gtest-all.cc.i

googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest.dir/src/gtest-all.cc.s"
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && /Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/googletest/src/gtest-all.cc -o CMakeFiles/gtest.dir/src/gtest-all.cc.s

# Object files for target gtest
gtest_OBJECTS = \
"CMakeFiles/gtest.dir/src/gtest-all.cc.o"

# External object files for target gtest
gtest_EXTERNAL_OBJECTS =

googlemock/gtest/libgtest.a: googlemock/gtest/CMakeFiles/gtest.dir/src/gtest-all.cc.o
googlemock/gtest/libgtest.a: googlemock/gtest/CMakeFiles/gtest.dir/build.make
googlemock/gtest/libgtest.a: googlemock/gtest/CMakeFiles/gtest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libgtest.a"
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean_target.cmake
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googlemock/gtest/CMakeFiles/gtest.dir/build: googlemock/gtest/libgtest.a
.PHONY : googlemock/gtest/CMakeFiles/gtest.dir/build

googlemock/gtest/CMakeFiles/gtest.dir/clean:
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest.dir/cmake_clean.cmake
.PHONY : googlemock/gtest/CMakeFiles/gtest.dir/clean

googlemock/gtest/CMakeFiles/gtest.dir/depend:
	cd /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1 /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/googletest /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest /Users/hiro/42/webserv/other/google_test/googletest/source/googletest-release-1.8.1/build/googlemock/gtest/CMakeFiles/gtest.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googlemock/gtest/CMakeFiles/gtest.dir/depend

