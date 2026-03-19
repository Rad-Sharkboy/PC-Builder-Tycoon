cmake_minimum_required(VERSION 3.15)

# Fix for CMake 4.0+ rejecting Raylib's older configuration format
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

project(RigBuilderTycoon VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Magically fetches and configures Raylib
include(FetchContent)
FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE 
)
FetchContent_MakeAvailable(raylib)

add_subdirectory(src)