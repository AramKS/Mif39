# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

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
CMAKE_SOURCE_DIR = /home/mica/Bureau/FAC/Mif39/C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mica/Bureau/FAC/Mif39/C++-build

# Include any dependencies generated for this target.
include Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/depend.make

# Include the progress variables for this target.
include Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/progress.make

# Include the compile flags for this target's objects.
include Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/flags.make

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/flags.make
Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o: /home/mica/Bureau/FAC/Mif39/C++/Samples/ThreadedServer/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/mica/Bureau/FAC/Mif39/C++-build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o"
	cd /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/ThreadedServer.dir/main.cpp.o -c /home/mica/Bureau/FAC/Mif39/C++/Samples/ThreadedServer/main.cpp

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ThreadedServer.dir/main.cpp.i"
	cd /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/mica/Bureau/FAC/Mif39/C++/Samples/ThreadedServer/main.cpp > CMakeFiles/ThreadedServer.dir/main.cpp.i

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ThreadedServer.dir/main.cpp.s"
	cd /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/mica/Bureau/FAC/Mif39/C++/Samples/ThreadedServer/main.cpp -o CMakeFiles/ThreadedServer.dir/main.cpp.s

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.requires:
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.requires

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.provides: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.requires
	$(MAKE) -f Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/build.make Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.provides.build
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.provides

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.provides.build: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o

# Object files for target ThreadedServer
ThreadedServer_OBJECTS = \
"CMakeFiles/ThreadedServer.dir/main.cpp.o"

# External object files for target ThreadedServer
ThreadedServer_EXTERNAL_OBJECTS =

bin/ThreadedServer: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o
bin/ThreadedServer: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/build.make
bin/ThreadedServer: /opt/Qt/5.4/gcc_64/lib/libQt5Core.so.5.4.0
bin/ThreadedServer: /opt/Qt/5.4/gcc_64/lib/libQt5Gui.so.5.4.0
bin/ThreadedServer: lib/libUtility.so
bin/ThreadedServer: lib/libNetworking.so
bin/ThreadedServer: lib/libTcpNetworking.so
bin/ThreadedServer: lib/libAssetInterfaces.so
bin/ThreadedServer: lib/libAssetGenerics.so
bin/ThreadedServer: lib/libAssets.so
bin/ThreadedServer: lib/libWavefront.so
bin/ThreadedServer: lib/libQImageLoader.so
bin/ThreadedServer: lib/libNetworking.so
bin/ThreadedServer: lib/libAssets.so
bin/ThreadedServer: lib/libAssetGenerics.so
bin/ThreadedServer: lib/libAssetInterfaces.so
bin/ThreadedServer: lib/libUtility.so
bin/ThreadedServer: /opt/Qt/5.4/gcc_64/lib/libQt5Gui.so.5.4.0
bin/ThreadedServer: /opt/Qt/5.4/gcc_64/lib/libQt5Core.so.5.4.0
bin/ThreadedServer: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable ../../bin/ThreadedServer"
	cd /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ThreadedServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/build: bin/ThreadedServer
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/build

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/requires: Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/main.cpp.o.requires
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/requires

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/clean:
	cd /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer && $(CMAKE_COMMAND) -P CMakeFiles/ThreadedServer.dir/cmake_clean.cmake
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/clean

Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/depend:
	cd /home/mica/Bureau/FAC/Mif39/C++-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mica/Bureau/FAC/Mif39/C++ /home/mica/Bureau/FAC/Mif39/C++/Samples/ThreadedServer /home/mica/Bureau/FAC/Mif39/C++-build /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer /home/mica/Bureau/FAC/Mif39/C++-build/Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Samples/ThreadedServer/CMakeFiles/ThreadedServer.dir/depend

