cmake_minimum_required(VERSION 2.6)
set(CMAKE_BUILD_TYPE Debug)  # Enables debug mode
add_subdirectory(src) # directory you want to add or contains executable files
set(CMAKE_CXX_FLAGS_DEBUG "-g")  # Adds debug symbols
