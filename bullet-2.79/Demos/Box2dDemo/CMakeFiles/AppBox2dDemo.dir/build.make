# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canoncical targets will work.
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

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /v/filer4b/v38q001/ruoyi/bullet-2.79

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /v/filer4b/v38q001/ruoyi/bullet-2.79

# Include any dependencies generated for this target.
include Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/flags.make

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/flags.make
Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o: Demos/Box2dDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/ruoyi/bullet-2.79/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppBox2dDemo.dir/main.o -c /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/main.cpp

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppBox2dDemo.dir/main.i"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/main.cpp > CMakeFiles/AppBox2dDemo.dir/main.i

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppBox2dDemo.dir/main.s"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/main.cpp -o CMakeFiles/AppBox2dDemo.dir/main.s

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.requires:
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.requires

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.provides: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.requires
	$(MAKE) -f Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/build.make Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.provides.build
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.provides

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.provides.build: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.provides.build

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/flags.make
Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o: Demos/Box2dDemo/Box2dDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/ruoyi/bullet-2.79/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o -c /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/Box2dDemo.cpp

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppBox2dDemo.dir/Box2dDemo.i"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/Box2dDemo.cpp > CMakeFiles/AppBox2dDemo.dir/Box2dDemo.i

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppBox2dDemo.dir/Box2dDemo.s"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/Box2dDemo.cpp -o CMakeFiles/AppBox2dDemo.dir/Box2dDemo.s

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.requires:
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.requires

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.provides: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.requires
	$(MAKE) -f Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/build.make Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.provides.build
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.provides

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.provides.build: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.provides.build

# Object files for target AppBox2dDemo
AppBox2dDemo_OBJECTS = \
"CMakeFiles/AppBox2dDemo.dir/main.o" \
"CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o"

# External object files for target AppBox2dDemo
AppBox2dDemo_EXTERNAL_OBJECTS =

Demos/Box2dDemo/AppBox2dDemo: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o
Demos/Box2dDemo/AppBox2dDemo: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o
Demos/Box2dDemo/AppBox2dDemo: Demos/OpenGL/libOpenGLSupport.so
Demos/Box2dDemo/AppBox2dDemo: src/BulletDynamics/libBulletDynamics.so.2.79
Demos/Box2dDemo/AppBox2dDemo: src/BulletCollision/libBulletCollision.so.2.79
Demos/Box2dDemo/AppBox2dDemo: src/LinearMath/libLinearMath.so.2.79
Demos/Box2dDemo/AppBox2dDemo: /usr/lib/libglut.so
Demos/Box2dDemo/AppBox2dDemo: /usr/lib/libGL.so
Demos/Box2dDemo/AppBox2dDemo: /usr/lib/libGLU.so
Demos/Box2dDemo/AppBox2dDemo: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/build.make
Demos/Box2dDemo/AppBox2dDemo: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppBox2dDemo"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppBox2dDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/build: Demos/Box2dDemo/AppBox2dDemo
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/build

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/requires: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/main.o.requires
Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/requires: Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/Box2dDemo.o.requires
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/requires

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/clean:
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppBox2dDemo.dir/cmake_clean.cmake
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/clean

Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/depend:
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /v/filer4b/v38q001/ruoyi/bullet-2.79 /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo /v/filer4b/v38q001/ruoyi/bullet-2.79 /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/Box2dDemo/CMakeFiles/AppBox2dDemo.dir/depend

