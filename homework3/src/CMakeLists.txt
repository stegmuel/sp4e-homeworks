
cmake_minimum_required(VERSION 3.1)
project(Particles)

set(CMAKE_CXX_STANDARD 17)

# Set default build type to Debug if not specified
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# Add debug and release-specific flags
set(CMAKE_CXX_FLAGS_DEBUG "-g -O0" CACHE STRING "Debug flags" FORCE)  # Debug symbols
set(CMAKE_CXX_FLAGS_RELEASE "-O3" CACHE STRING "Release flags" FORCE) # High optimization for release

# Export compile commands for IDE tools
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

################################################################
# libpart
################################################################

add_library(part
  compute_boundary.cc
  compute_verlet_integration.cc 
  particle.cc 
  planet.cc
  compute_gravity.cc 
  csv_reader.cc 
  particles_factory_interface.cc 
  planets_factory.cc 
  compute_contact.cc 
  compute_kinetic_energy.cc 
  csv_writer.cc 
  system.cc 
  compute_energy.cc 
  compute_potential_energy.cc 
  ping_pong_ball.cc
  material_point.cc 
  system_evolution.cc 
  ping_pong_balls_factory.cc 
  compute_interaction.cc
  compute_temperature.cc
  material_points_factory.cc 
  )

# Add debug flags for the library
target_compile_options(part PRIVATE $<$<CONFIG:Debug>:-g>)

add_executable(particles main.cc)

# Add debug flags for the executable
target_compile_options(particles PRIVATE $<$<CONFIG:Debug>:-g>)

# Find FFTW library
option (USE_FFTW "Use FFTW ?" ON)
if(USE_FFTW)
  find_library(FFTW_LIBRARIES fftw3)
  if(FFTW_LIBRARIES)
    message(STATUS "FFTW library found: ${FFTW_LIBRARIES}")
  else()
    message(FATAL_ERROR "FFTW library not found!")
  endif()
else()
  message(STATUS "Not using FFTW!")
endif()

target_link_libraries(particles gtest_main gtest pthread part ${FFTW_LIBRARIES})

if(EXISTS "${PROJECT_SOURCE_DIR}/../googletest/CMakeLists.txt")
  add_subdirectory(${PROJECT_SOURCE_DIR}/../googletest googletest)
  add_executable(test_kepler test_kepler.cc)
  add_executable(test_fft test_fft.cc)
  add_executable(test_temperature test_temperature.cc)
  target_link_libraries(test_kepler part gtest_main gtest pthread )
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
  target_link_libraries(test_temperature part gtest_main gtest pthread ${FFTW_LIBRARIES})
  add_custom_target(test ./test_kepler && ./test_fft && ./test_temperature DEPENDS part test_kepler test_fft test_temperature)
else()
  message("
*********************************************
google tests is missing. 
Did you forget `git submodule update --init`
*********************************************
")
  message(FATAL_ERROR "exit")
endif()

################################################################
# Doxygen
################################################################

find_package(Doxygen)
if (DOXYGEN_FOUND)

  # to set other options, read: https://cmake.org/cmake/help/v3.9/module/FindDoxygen.html
  set(DOXYGEN_EXCLUDE_PATTERNS */googletest/*)

  doxygen_add_docs(
    doxygen
    ${PROJECT_SOURCE_DIR}
    COMMENT "Generate html pages"
    )
  add_custom_target(doc DEPENDS doxygen)
endif(DOXYGEN_FOUND)
