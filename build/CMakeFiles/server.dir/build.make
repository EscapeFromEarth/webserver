# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/abcpony/myProjects/Reactor_cppversion

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/abcpony/myProjects/Reactor_cppversion/build

# Include any dependencies generated for this target.
include CMakeFiles/server.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/server.dir/flags.make

CMakeFiles/server.dir/utils/acceptTask.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/acceptTask.cpp.o: ../utils/acceptTask.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/server.dir/utils/acceptTask.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/acceptTask.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/acceptTask.cpp

CMakeFiles/server.dir/utils/acceptTask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/acceptTask.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/acceptTask.cpp > CMakeFiles/server.dir/utils/acceptTask.cpp.i

CMakeFiles/server.dir/utils/acceptTask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/acceptTask.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/acceptTask.cpp -o CMakeFiles/server.dir/utils/acceptTask.cpp.s

CMakeFiles/server.dir/utils/communicationTask.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/communicationTask.cpp.o: ../utils/communicationTask.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/server.dir/utils/communicationTask.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/communicationTask.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/communicationTask.cpp

CMakeFiles/server.dir/utils/communicationTask.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/communicationTask.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/communicationTask.cpp > CMakeFiles/server.dir/utils/communicationTask.cpp.i

CMakeFiles/server.dir/utils/communicationTask.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/communicationTask.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/communicationTask.cpp -o CMakeFiles/server.dir/utils/communicationTask.cpp.s

CMakeFiles/server.dir/utils/logger.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/logger.cpp.o: ../utils/logger.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/server.dir/utils/logger.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/logger.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/logger.cpp

CMakeFiles/server.dir/utils/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/logger.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/logger.cpp > CMakeFiles/server.dir/utils/logger.cpp.i

CMakeFiles/server.dir/utils/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/logger.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/logger.cpp -o CMakeFiles/server.dir/utils/logger.cpp.s

CMakeFiles/server.dir/utils/server.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/server.cpp.o: ../utils/server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/server.dir/utils/server.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/server.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/server.cpp

CMakeFiles/server.dir/utils/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/server.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/server.cpp > CMakeFiles/server.dir/utils/server.cpp.i

CMakeFiles/server.dir/utils/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/server.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/server.cpp -o CMakeFiles/server.dir/utils/server.cpp.s

CMakeFiles/server.dir/utils/task.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/task.cpp.o: ../utils/task.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/server.dir/utils/task.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/task.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/task.cpp

CMakeFiles/server.dir/utils/task.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/task.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/task.cpp > CMakeFiles/server.dir/utils/task.cpp.i

CMakeFiles/server.dir/utils/task.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/task.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/task.cpp -o CMakeFiles/server.dir/utils/task.cpp.s

CMakeFiles/server.dir/utils/taskQueue.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/taskQueue.cpp.o: ../utils/taskQueue.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/server.dir/utils/taskQueue.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/taskQueue.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/taskQueue.cpp

CMakeFiles/server.dir/utils/taskQueue.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/taskQueue.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/taskQueue.cpp > CMakeFiles/server.dir/utils/taskQueue.cpp.i

CMakeFiles/server.dir/utils/taskQueue.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/taskQueue.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/taskQueue.cpp -o CMakeFiles/server.dir/utils/taskQueue.cpp.s

CMakeFiles/server.dir/utils/threadPool.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/utils/threadPool.cpp.o: ../utils/threadPool.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/server.dir/utils/threadPool.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/utils/threadPool.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/utils/threadPool.cpp

CMakeFiles/server.dir/utils/threadPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/utils/threadPool.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/utils/threadPool.cpp > CMakeFiles/server.dir/utils/threadPool.cpp.i

CMakeFiles/server.dir/utils/threadPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/utils/threadPool.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/utils/threadPool.cpp -o CMakeFiles/server.dir/utils/threadPool.cpp.s

CMakeFiles/server.dir/main.cpp.o: CMakeFiles/server.dir/flags.make
CMakeFiles/server.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/server.dir/main.cpp.o"
	/usr/bin/g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/server.dir/main.cpp.o -c /home/abcpony/myProjects/Reactor_cppversion/main.cpp

CMakeFiles/server.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/server.dir/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/abcpony/myProjects/Reactor_cppversion/main.cpp > CMakeFiles/server.dir/main.cpp.i

CMakeFiles/server.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/server.dir/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/abcpony/myProjects/Reactor_cppversion/main.cpp -o CMakeFiles/server.dir/main.cpp.s

# Object files for target server
server_OBJECTS = \
"CMakeFiles/server.dir/utils/acceptTask.cpp.o" \
"CMakeFiles/server.dir/utils/communicationTask.cpp.o" \
"CMakeFiles/server.dir/utils/logger.cpp.o" \
"CMakeFiles/server.dir/utils/server.cpp.o" \
"CMakeFiles/server.dir/utils/task.cpp.o" \
"CMakeFiles/server.dir/utils/taskQueue.cpp.o" \
"CMakeFiles/server.dir/utils/threadPool.cpp.o" \
"CMakeFiles/server.dir/main.cpp.o"

# External object files for target server
server_EXTERNAL_OBJECTS =

server: CMakeFiles/server.dir/utils/acceptTask.cpp.o
server: CMakeFiles/server.dir/utils/communicationTask.cpp.o
server: CMakeFiles/server.dir/utils/logger.cpp.o
server: CMakeFiles/server.dir/utils/server.cpp.o
server: CMakeFiles/server.dir/utils/task.cpp.o
server: CMakeFiles/server.dir/utils/taskQueue.cpp.o
server: CMakeFiles/server.dir/utils/threadPool.cpp.o
server: CMakeFiles/server.dir/main.cpp.o
server: CMakeFiles/server.dir/build.make
server: CMakeFiles/server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/server.dir/build: server

.PHONY : CMakeFiles/server.dir/build

CMakeFiles/server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/server.dir/clean

CMakeFiles/server.dir/depend:
	cd /home/abcpony/myProjects/Reactor_cppversion/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/abcpony/myProjects/Reactor_cppversion /home/abcpony/myProjects/Reactor_cppversion /home/abcpony/myProjects/Reactor_cppversion/build /home/abcpony/myProjects/Reactor_cppversion/build /home/abcpony/myProjects/Reactor_cppversion/build/CMakeFiles/server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/server.dir/depend

