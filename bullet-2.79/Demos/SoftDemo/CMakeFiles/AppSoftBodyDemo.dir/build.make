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
include Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/depend.make

# Include the progress variables for this target.
include Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/progress.make

# Include the compile flags for this target's objects.
include Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/flags.make

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/flags.make
Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o: Demos/SoftDemo/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/ruoyi/bullet-2.79/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppSoftBodyDemo.dir/main.o -c /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/main.cpp

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppSoftBodyDemo.dir/main.i"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/main.cpp > CMakeFiles/AppSoftBodyDemo.dir/main.i

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppSoftBodyDemo.dir/main.s"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/main.cpp -o CMakeFiles/AppSoftBodyDemo.dir/main.s

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.requires:
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.requires

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.provides: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.requires
	$(MAKE) -f Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/build.make Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.provides.build
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.provides

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.provides.build: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.provides.build

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/flags.make
Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o: Demos/SoftDemo/SoftDemo.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /v/filer4b/v38q001/ruoyi/bullet-2.79/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o -c /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/SoftDemo.cpp

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.i"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/SoftDemo.cpp > CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.i

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.s"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/SoftDemo.cpp -o CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.s

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.requires:
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.requires

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.provides: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.requires
	$(MAKE) -f Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/build.make Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.provides.build
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.provides

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.provides.build: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.provides.build

# Object files for target AppSoftBodyDemo
AppSoftBodyDemo_OBJECTS = \
"CMakeFiles/AppSoftBodyDemo.dir/main.o" \
"CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o"

# External object files for target AppSoftBodyDemo
AppSoftBodyDemo_EXTERNAL_OBJECTS =

Demos/SoftDemo/AppSoftBodyDemo: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o
Demos/SoftDemo/AppSoftBodyDemo: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o
Demos/SoftDemo/AppSoftBodyDemo: Demos/OpenGL/libOpenGLSupport.so
Demos/SoftDemo/AppSoftBodyDemo: src/BulletSoftBody/libBulletSoftBody.so.2.79
Demos/SoftDemo/AppSoftBodyDemo: src/BulletDynamics/libBulletDynamics.so.2.79
Demos/SoftDemo/AppSoftBodyDemo: src/BulletCollision/libBulletCollision.so.2.79
Demos/SoftDemo/AppSoftBodyDemo: src/LinearMath/libLinearMath.so.2.79
Demos/SoftDemo/AppSoftBodyDemo: /usr/lib/libglut.so
Demos/SoftDemo/AppSoftBodyDemo: /usr/lib/libGL.so
Demos/SoftDemo/AppSoftBodyDemo: /usr/lib/libGLU.so
Demos/SoftDemo/AppSoftBodyDemo: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/build.make
Demos/SoftDemo/AppSoftBodyDemo: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable AppSoftBodyDemo"
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AppSoftBodyDemo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/build: Demos/SoftDemo/AppSoftBodyDemo
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/build

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/requires: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/main.o.requires
Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/requires: Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/SoftDemo.o.requires
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/requires

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/clean:
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo && $(CMAKE_COMMAND) -P CMakeFiles/AppSoftBodyDemo.dir/cmake_clean.cmake
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/clean

Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/depend:
	cd /v/filer4b/v38q001/ruoyi/bullet-2.79 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /v/filer4b/v38q001/ruoyi/bullet-2.79 /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo /v/filer4b/v38q001/ruoyi/bullet-2.79 /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo /v/filer4b/v38q001/ruoyi/bullet-2.79/Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : Demos/SoftDemo/CMakeFiles/AppSoftBodyDemo.dir/depend

