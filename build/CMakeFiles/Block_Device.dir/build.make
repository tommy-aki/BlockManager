# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build"

# Include any dependencies generated for this target.
include CMakeFiles/Block_Device.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/Block_Device.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/Block_Device.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Block_Device.dir/flags.make

CMakeFiles/Block_Device.dir/blockDevice.cpp.o: CMakeFiles/Block_Device.dir/flags.make
CMakeFiles/Block_Device.dir/blockDevice.cpp.o: ../blockDevice.cpp
CMakeFiles/Block_Device.dir/blockDevice.cpp.o: CMakeFiles/Block_Device.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Block_Device.dir/blockDevice.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Block_Device.dir/blockDevice.cpp.o -MF CMakeFiles/Block_Device.dir/blockDevice.cpp.o.d -o CMakeFiles/Block_Device.dir/blockDevice.cpp.o -c "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/blockDevice.cpp"

CMakeFiles/Block_Device.dir/blockDevice.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Block_Device.dir/blockDevice.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/blockDevice.cpp" > CMakeFiles/Block_Device.dir/blockDevice.cpp.i

CMakeFiles/Block_Device.dir/blockDevice.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Block_Device.dir/blockDevice.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/blockDevice.cpp" -o CMakeFiles/Block_Device.dir/blockDevice.cpp.s

CMakeFiles/Block_Device.dir/main.cpp.o: CMakeFiles/Block_Device.dir/flags.make
CMakeFiles/Block_Device.dir/main.cpp.o: ../main.cpp
CMakeFiles/Block_Device.dir/main.cpp.o: CMakeFiles/Block_Device.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Block_Device.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/Block_Device.dir/main.cpp.o -MF CMakeFiles/Block_Device.dir/main.cpp.o.d -o CMakeFiles/Block_Device.dir/main.cpp.o -c "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/main.cpp"

CMakeFiles/Block_Device.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Block_Device.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/main.cpp" > CMakeFiles/Block_Device.dir/main.cpp.i

CMakeFiles/Block_Device.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Block_Device.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/main.cpp" -o CMakeFiles/Block_Device.dir/main.cpp.s

# Object files for target Block_Device
Block_Device_OBJECTS = \
"CMakeFiles/Block_Device.dir/blockDevice.cpp.o" \
"CMakeFiles/Block_Device.dir/main.cpp.o"

# External object files for target Block_Device
Block_Device_EXTERNAL_OBJECTS =

Block_Device: CMakeFiles/Block_Device.dir/blockDevice.cpp.o
Block_Device: CMakeFiles/Block_Device.dir/main.cpp.o
Block_Device: CMakeFiles/Block_Device.dir/build.make
Block_Device: CMakeFiles/Block_Device.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable Block_Device"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Block_Device.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Block_Device.dir/build: Block_Device
.PHONY : CMakeFiles/Block_Device.dir/build

CMakeFiles/Block_Device.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Block_Device.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Block_Device.dir/clean

CMakeFiles/Block_Device.dir/depend:
	cd "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon" "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon" "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build" "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build" "/mnt/c/Users/Tommy Lee Pon/OneDrive/Documentos/UNITEC ARCHIVOS/Estru Datos 2/20241112_Proyecto1eraEntrega_TommyPon/build/CMakeFiles/Block_Device.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Block_Device.dir/depend

