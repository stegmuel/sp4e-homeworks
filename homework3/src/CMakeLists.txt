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


################################################################
# FFTW
################################################################
option (USE_FFTW "Use FFTW ?" ON)
if(USE_FFTW)
    find_library(FFTW_LIBRARIES fftw3) # Requires FFTW3 development package
    if(FFTW_LIBRARIES)
        message(STATUS "FFTW found: ${FFTW_LIBRARIES}")
        set(HAS_FFTW 1)
    else()
        message(FATAL_ERROR "FFTW not found")
    endif()
else()
    set(HAS_FFTW 0)
endif()

add_executable(particles main.cc)

if(HAS_FFTW)
  target_link_libraries(particles gtest_main gtest pthread part ${FFTW_LIBRARIES})
else()
  target_link_libraries(particles gtest_main gtest pthread part)
endif()

################################################################
# GoogleTest
################################################################
add_executable(test_kepler test_kepler.cc)
add_executable(test_fft test_fft.cc)
target_link_libraries(test_kepler part gtest_main gtest pthread )
if(HAS_FFTW)
  target_link_libraries(test_fft part gtest_main gtest pthread ${FFTW_LIBRARIES})
else()
  target_link_libraries(test_fft part gtest_main gtest pthread)
endif()
add_custom_target(test ./test_kepler && ./test_fft DEPENDS part test_kepler test_fft)

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
