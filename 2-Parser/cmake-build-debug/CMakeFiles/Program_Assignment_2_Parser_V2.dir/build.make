# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.17

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


.SUFFIXES: .hpux_make_needs_suffix_list


# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles\Program_Assignment_2_Parser_V2.dir\depend.make

# Include the progress variables for this target.
include CMakeFiles\Program_Assignment_2_Parser_V2.dir\progress.make

# Include the compile flags for this target's objects.
include CMakeFiles\Program_Assignment_2_Parser_V2.dir\flags.make

CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.obj: CMakeFiles\Program_Assignment_2_Parser_V2.dir\flags.make
CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.obj: ..\lex.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Program_Assignment_2_Parser_V2.dir/lex.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.obj /FdCMakeFiles\Program_Assignment_2_Parser_V2.dir\ /FS -c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\lex.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Program_Assignment_2_Parser_V2.dir/lex.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\lex.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Program_Assignment_2_Parser_V2.dir/lex.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.s /c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\lex.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.obj: CMakeFiles\Program_Assignment_2_Parser_V2.dir\flags.make
CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.obj: ..\prog2.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/Program_Assignment_2_Parser_V2.dir/prog2.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.obj /FdCMakeFiles\Program_Assignment_2_Parser_V2.dir\ /FS -c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\prog2.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Program_Assignment_2_Parser_V2.dir/prog2.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\prog2.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Program_Assignment_2_Parser_V2.dir/prog2.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.s /c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\prog2.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.obj: CMakeFiles\Program_Assignment_2_Parser_V2.dir\flags.make
CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.obj: ..\parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/Program_Assignment_2_Parser_V2.dir/parse.cpp.obj"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.obj /FdCMakeFiles\Program_Assignment_2_Parser_V2.dir\ /FS -c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\parse.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Program_Assignment_2_Parser_V2.dir/parse.cpp.i"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe > CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\parse.cpp"
<<

CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Program_Assignment_2_Parser_V2.dir/parse.cpp.s"
	C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.s /c "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\parse.cpp"
<<

# Object files for target Program_Assignment_2_Parser_V2
Program_Assignment_2_Parser_V2_OBJECTS = \
"CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.obj" \
"CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.obj" \
"CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.obj"

# External object files for target Program_Assignment_2_Parser_V2
Program_Assignment_2_Parser_V2_EXTERNAL_OBJECTS =

Program_Assignment_2_Parser_V2.exe: CMakeFiles\Program_Assignment_2_Parser_V2.dir\lex.cpp.obj
Program_Assignment_2_Parser_V2.exe: CMakeFiles\Program_Assignment_2_Parser_V2.dir\prog2.cpp.obj
Program_Assignment_2_Parser_V2.exe: CMakeFiles\Program_Assignment_2_Parser_V2.dir\parse.cpp.obj
Program_Assignment_2_Parser_V2.exe: CMakeFiles\Program_Assignment_2_Parser_V2.dir\build.make
Program_Assignment_2_Parser_V2.exe: CMakeFiles\Program_Assignment_2_Parser_V2.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable Program_Assignment_2_Parser_V2.exe"
	"C:\Program Files\JetBrains\CLion 2020.3.2\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\Program_Assignment_2_Parser_V2.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100183~1.0\x86\mt.exe --manifests  -- C:\PROGRA~2\MICROS~4\2019\COMMUN~1\VC\Tools\MSVC\1423~1.281\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\Program_Assignment_2_Parser_V2.dir\objects1.rsp @<<
 /out:Program_Assignment_2_Parser_V2.exe /implib:Program_Assignment_2_Parser_V2.lib /pdb:"C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\Program_Assignment_2_Parser_V2.pdb" /version:0.0  /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<

# Rule to build all files generated by this target.
CMakeFiles\Program_Assignment_2_Parser_V2.dir\build: Program_Assignment_2_Parser_V2.exe

.PHONY : CMakeFiles\Program_Assignment_2_Parser_V2.dir\build

CMakeFiles\Program_Assignment_2_Parser_V2.dir\clean:
	$(CMAKE_COMMAND) -P CMakeFiles\Program_Assignment_2_Parser_V2.dir\cmake_clean.cmake
.PHONY : CMakeFiles\Program_Assignment_2_Parser_V2.dir\clean

CMakeFiles\Program_Assignment_2_Parser_V2.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser" "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser" "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug" "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug" "C:\Dev C++\CS280 Programming Language Concepts\Program Assignment 2 Parser\cmake-build-debug\CMakeFiles\Program_Assignment_2_Parser_V2.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles\Program_Assignment_2_Parser_V2.dir\depend
