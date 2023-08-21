# CMakeList.txt : CMake project for libKsc, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.12)

project ("SimpleTicTacToe" VERSION 1.0.0 DESCRIPTION "A Simple Tic-Tac-Toe Game")

# Add source to this project's executable.
add_executable (tictactoe "main.cpp")

set_property(TARGET tictactoe PROPERTY CXX_STANDARD 17)

# TODO: Add tests and install targets if needed.
