cmake_minimum_required(VERSION 3.20)

# Project name and language
project(socket VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Include folder
include_directories(include)

# List all source files
set(SOURCES
    src/main.cpp
    src/busqueda.cpp
    src/mapa.cpp
    src/robot.cpp
)

# Create executable
add_executable(busqueda ${SOURCES})

# Optional: compiler warnings
target_compile_options(busqueda PRIVATE -Wall -Wextra -Wpedantic)

