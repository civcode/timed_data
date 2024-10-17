# Specify the minimum version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(TimedDataExample VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Add the executable
add_executable(TimedDataExample src/main.cpp)

# Include the current directory so the compiler can find the header file
target_include_directories(TimedDataExample PUBLIC "${PROJECT_SOURCE_DIR}/include")
