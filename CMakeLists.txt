cmake_minimum_required(VERSION 3.10)

# Project Name
project(StableMarriageProblemTool CXX)

# Enforce C++17 Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gather all source files from the src directory
file(GLOB SOURCES "src/*.cpp")

# Define the executable and its source files
add_executable(StableMarriageApp ${SOURCES})

# Specify include directories
target_include_directories(StableMarriageApp PUBLIC include)
