cmake_minimum_required(VERSION 3.25)
project(chess-minimax-AI)

set(CMAKE_CXX_STANDARD 23)

add_executable(chess-minimax-AI src/main.cpp include/Node.h src/Node.cpp include/Minimax.h src/Minimax.cpp)

target_include_directories(chess-minimax-AI PRIVATE include)
