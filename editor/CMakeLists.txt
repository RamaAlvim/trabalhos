cmake_minimum_required(VERSION 3.2)
project(editor_grafo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(editor_grafo ${SOURCE_FILES})