# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/router/Documents/muduo_example/chat_server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/router/Documents/muduo_example/chat_server

# Include any dependencies generated for this target.
include CMakeFiles/chat_server_highperform.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/chat_server_highperform.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/chat_server_highperform.dir/flags.make

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o: CMakeFiles/chat_server_highperform.dir/flags.make
CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o: chat_server_highperform.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/router/Documents/muduo_example/chat_server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o -c /home/router/Documents/muduo_example/chat_server/chat_server_highperform.cc

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/router/Documents/muduo_example/chat_server/chat_server_highperform.cc > CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.i

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/router/Documents/muduo_example/chat_server/chat_server_highperform.cc -o CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.s

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.requires:

.PHONY : CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.requires

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.provides: CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.requires
	$(MAKE) -f CMakeFiles/chat_server_highperform.dir/build.make CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.provides.build
.PHONY : CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.provides

CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.provides.build: CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o


# Object files for target chat_server_highperform
chat_server_highperform_OBJECTS = \
"CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o"

# External object files for target chat_server_highperform
chat_server_highperform_EXTERNAL_OBJECTS =

bin/chat_server_highperform: CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o
bin/chat_server_highperform: CMakeFiles/chat_server_highperform.dir/build.make
bin/chat_server_highperform: CMakeFiles/chat_server_highperform.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/router/Documents/muduo_example/chat_server/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bin/chat_server_highperform"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/chat_server_highperform.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/chat_server_highperform.dir/build: bin/chat_server_highperform

.PHONY : CMakeFiles/chat_server_highperform.dir/build

CMakeFiles/chat_server_highperform.dir/requires: CMakeFiles/chat_server_highperform.dir/chat_server_highperform.cc.o.requires

.PHONY : CMakeFiles/chat_server_highperform.dir/requires

CMakeFiles/chat_server_highperform.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/chat_server_highperform.dir/cmake_clean.cmake
.PHONY : CMakeFiles/chat_server_highperform.dir/clean

CMakeFiles/chat_server_highperform.dir/depend:
	cd /home/router/Documents/muduo_example/chat_server && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/router/Documents/muduo_example/chat_server /home/router/Documents/muduo_example/chat_server /home/router/Documents/muduo_example/chat_server /home/router/Documents/muduo_example/chat_server /home/router/Documents/muduo_example/chat_server/CMakeFiles/chat_server_highperform.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/chat_server_highperform.dir/depend

