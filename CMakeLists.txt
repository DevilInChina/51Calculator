cmake_minimum_required(VERSION 3.16)
project(AutoMachineGenerator)

SET(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR})

set(CMAKE_CXX_STANDARD 14)

add_executable(AutoMachineGenerator main.cpp)