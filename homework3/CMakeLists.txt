cmake_minimum_required (VERSION 3.1)
project (Particles)
set(CMAKE_BUILD_TYPE Debug)  # Enables debug mode
add_subdirectory(src) # directory you want to add or contains executable files
add_subdirectory(googletest)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS_DEBUG "-g")  # Adds debug symbols
