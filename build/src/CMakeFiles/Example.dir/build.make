# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.24

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.24.1/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.24.1/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build"

# Include any dependencies generated for this target.
include src/CMakeFiles/Example.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/Example.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/Example.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/Example.dir/flags.make

src/CMakeFiles/Example.dir/example.cpp.o: src/CMakeFiles/Example.dir/flags.make
src/CMakeFiles/Example.dir/example.cpp.o: /Users/akshay/Dropbox/My\ Mac\ (Akshay’s\ MacBook\ Air)/Documents/Machine\ Learning/Programming\ Practice/CSE\ 167\ Computer\ Graphics/src/example.cpp
src/CMakeFiles/Example.dir/example.cpp.o: src/CMakeFiles/Example.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/Example.dir/example.cpp.o"
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/Example.dir/example.cpp.o -MF CMakeFiles/Example.dir/example.cpp.o.d -o CMakeFiles/Example.dir/example.cpp.o -c "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/src/example.cpp"

src/CMakeFiles/Example.dir/example.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Example.dir/example.cpp.i"
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/src/example.cpp" > CMakeFiles/Example.dir/example.cpp.i

src/CMakeFiles/Example.dir/example.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Example.dir/example.cpp.s"
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" && /usr/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/src/example.cpp" -o CMakeFiles/Example.dir/example.cpp.s

# Object files for target Example
Example_OBJECTS = \
"CMakeFiles/Example.dir/example.cpp.o"

# External object files for target Example
Example_EXTERNAL_OBJECTS =

src/Example: src/CMakeFiles/Example.dir/example.cpp.o
src/Example: src/CMakeFiles/Example.dir/build.make
src/Example: src/CMakeFiles/Example.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Example"
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Example.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/Example.dir/build: src/Example
.PHONY : src/CMakeFiles/Example.dir/build

src/CMakeFiles/Example.dir/clean:
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" && $(CMAKE_COMMAND) -P CMakeFiles/Example.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/Example.dir/clean

src/CMakeFiles/Example.dir/depend:
	cd "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics" "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/src" "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build" "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src" "/Users/akshay/Dropbox/My Mac (Akshay’s MacBook Air)/Documents/Machine Learning/Programming Practice/CSE 167 Computer Graphics/build/src/CMakeFiles/Example.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : src/CMakeFiles/Example.dir/depend

