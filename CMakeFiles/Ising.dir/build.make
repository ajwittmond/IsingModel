# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_SOURCE_DIR = /home/alexanderwittmond/code/c++/IsingModel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alexanderwittmond/code/c++/IsingModel

# Include any dependencies generated for this target.
include CMakeFiles/Ising.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ising.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ising.dir/flags.make

CMakeFiles/Ising.dir/main.cpp.o: CMakeFiles/Ising.dir/flags.make
CMakeFiles/Ising.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexanderwittmond/code/c++/IsingModel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Ising.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ising.dir/main.cpp.o -c /home/alexanderwittmond/code/c++/IsingModel/main.cpp

CMakeFiles/Ising.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ising.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexanderwittmond/code/c++/IsingModel/main.cpp > CMakeFiles/Ising.dir/main.cpp.i

CMakeFiles/Ising.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ising.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexanderwittmond/code/c++/IsingModel/main.cpp -o CMakeFiles/Ising.dir/main.cpp.s

CMakeFiles/Ising.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/Ising.dir/main.cpp.o.requires

CMakeFiles/Ising.dir/main.cpp.o.provides: CMakeFiles/Ising.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/Ising.dir/build.make CMakeFiles/Ising.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/Ising.dir/main.cpp.o.provides

CMakeFiles/Ising.dir/main.cpp.o.provides.build: CMakeFiles/Ising.dir/main.cpp.o


CMakeFiles/Ising.dir/isingWindow.cpp.o: CMakeFiles/Ising.dir/flags.make
CMakeFiles/Ising.dir/isingWindow.cpp.o: isingWindow.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexanderwittmond/code/c++/IsingModel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Ising.dir/isingWindow.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ising.dir/isingWindow.cpp.o -c /home/alexanderwittmond/code/c++/IsingModel/isingWindow.cpp

CMakeFiles/Ising.dir/isingWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ising.dir/isingWindow.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexanderwittmond/code/c++/IsingModel/isingWindow.cpp > CMakeFiles/Ising.dir/isingWindow.cpp.i

CMakeFiles/Ising.dir/isingWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ising.dir/isingWindow.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexanderwittmond/code/c++/IsingModel/isingWindow.cpp -o CMakeFiles/Ising.dir/isingWindow.cpp.s

CMakeFiles/Ising.dir/isingWindow.cpp.o.requires:

.PHONY : CMakeFiles/Ising.dir/isingWindow.cpp.o.requires

CMakeFiles/Ising.dir/isingWindow.cpp.o.provides: CMakeFiles/Ising.dir/isingWindow.cpp.o.requires
	$(MAKE) -f CMakeFiles/Ising.dir/build.make CMakeFiles/Ising.dir/isingWindow.cpp.o.provides.build
.PHONY : CMakeFiles/Ising.dir/isingWindow.cpp.o.provides

CMakeFiles/Ising.dir/isingWindow.cpp.o.provides.build: CMakeFiles/Ising.dir/isingWindow.cpp.o


CMakeFiles/Ising.dir/ticker.cpp.o: CMakeFiles/Ising.dir/flags.make
CMakeFiles/Ising.dir/ticker.cpp.o: ticker.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexanderwittmond/code/c++/IsingModel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Ising.dir/ticker.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ising.dir/ticker.cpp.o -c /home/alexanderwittmond/code/c++/IsingModel/ticker.cpp

CMakeFiles/Ising.dir/ticker.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ising.dir/ticker.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexanderwittmond/code/c++/IsingModel/ticker.cpp > CMakeFiles/Ising.dir/ticker.cpp.i

CMakeFiles/Ising.dir/ticker.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ising.dir/ticker.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexanderwittmond/code/c++/IsingModel/ticker.cpp -o CMakeFiles/Ising.dir/ticker.cpp.s

CMakeFiles/Ising.dir/ticker.cpp.o.requires:

.PHONY : CMakeFiles/Ising.dir/ticker.cpp.o.requires

CMakeFiles/Ising.dir/ticker.cpp.o.provides: CMakeFiles/Ising.dir/ticker.cpp.o.requires
	$(MAKE) -f CMakeFiles/Ising.dir/build.make CMakeFiles/Ising.dir/ticker.cpp.o.provides.build
.PHONY : CMakeFiles/Ising.dir/ticker.cpp.o.provides

CMakeFiles/Ising.dir/ticker.cpp.o.provides.build: CMakeFiles/Ising.dir/ticker.cpp.o


CMakeFiles/Ising.dir/model.cpp.o: CMakeFiles/Ising.dir/flags.make
CMakeFiles/Ising.dir/model.cpp.o: model.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alexanderwittmond/code/c++/IsingModel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/Ising.dir/model.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Ising.dir/model.cpp.o -c /home/alexanderwittmond/code/c++/IsingModel/model.cpp

CMakeFiles/Ising.dir/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Ising.dir/model.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alexanderwittmond/code/c++/IsingModel/model.cpp > CMakeFiles/Ising.dir/model.cpp.i

CMakeFiles/Ising.dir/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Ising.dir/model.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alexanderwittmond/code/c++/IsingModel/model.cpp -o CMakeFiles/Ising.dir/model.cpp.s

CMakeFiles/Ising.dir/model.cpp.o.requires:

.PHONY : CMakeFiles/Ising.dir/model.cpp.o.requires

CMakeFiles/Ising.dir/model.cpp.o.provides: CMakeFiles/Ising.dir/model.cpp.o.requires
	$(MAKE) -f CMakeFiles/Ising.dir/build.make CMakeFiles/Ising.dir/model.cpp.o.provides.build
.PHONY : CMakeFiles/Ising.dir/model.cpp.o.provides

CMakeFiles/Ising.dir/model.cpp.o.provides.build: CMakeFiles/Ising.dir/model.cpp.o


# Object files for target Ising
Ising_OBJECTS = \
"CMakeFiles/Ising.dir/main.cpp.o" \
"CMakeFiles/Ising.dir/isingWindow.cpp.o" \
"CMakeFiles/Ising.dir/ticker.cpp.o" \
"CMakeFiles/Ising.dir/model.cpp.o"

# External object files for target Ising
Ising_EXTERNAL_OBJECTS =

Ising: CMakeFiles/Ising.dir/main.cpp.o
Ising: CMakeFiles/Ising.dir/isingWindow.cpp.o
Ising: CMakeFiles/Ising.dir/ticker.cpp.o
Ising: CMakeFiles/Ising.dir/model.cpp.o
Ising: CMakeFiles/Ising.dir/build.make
Ising: CMakeFiles/Ising.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alexanderwittmond/code/c++/IsingModel/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable Ising"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ising.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ising.dir/build: Ising

.PHONY : CMakeFiles/Ising.dir/build

CMakeFiles/Ising.dir/requires: CMakeFiles/Ising.dir/main.cpp.o.requires
CMakeFiles/Ising.dir/requires: CMakeFiles/Ising.dir/isingWindow.cpp.o.requires
CMakeFiles/Ising.dir/requires: CMakeFiles/Ising.dir/ticker.cpp.o.requires
CMakeFiles/Ising.dir/requires: CMakeFiles/Ising.dir/model.cpp.o.requires

.PHONY : CMakeFiles/Ising.dir/requires

CMakeFiles/Ising.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ising.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ising.dir/clean

CMakeFiles/Ising.dir/depend:
	cd /home/alexanderwittmond/code/c++/IsingModel && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alexanderwittmond/code/c++/IsingModel /home/alexanderwittmond/code/c++/IsingModel /home/alexanderwittmond/code/c++/IsingModel /home/alexanderwittmond/code/c++/IsingModel /home/alexanderwittmond/code/c++/IsingModel/CMakeFiles/Ising.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ising.dir/depend

