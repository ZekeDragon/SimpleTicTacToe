# CMakeList.txt : CMake project for libKsc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("SimpleTicTacToe" VERSION 0.0.1 DESCRIPTION "A Simple Tic-Tac-Toe Game")

# Add source to this project's executable.
add_executable (ticTacToe "main.cpp")

set_property(TARGET ticTacToe PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
