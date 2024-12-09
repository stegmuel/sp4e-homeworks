#include "compute_temperature.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include "material_points_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>
#include <vector>
#include "vector.hh"


class RandomMaterialPoints : public ::testing::Test {
protected:
  void SetUp() override {
    // Initialize the factory of material points
    MaterialPointsFactory::getInstance();

    // Instantiate a vector of points
    std::vector<MaterialPoint> material_points;

    // Set the grid attributes
    n_points = 81;
    grid_size = sqrt(n_points);
    x_min = -1.;
    x_max = 1.;
    y_min = -1.;
    y_max = 1.;
    delta_xy = (x_max - x_min) / (grid_size - 1);
    L = x_max - x_min;

    // Instantiate all points in the grid
    for (UInt row = 0; row < grid_size; ++row) {
      for (UInt col = 0; col < grid_size; ++col) {
        // Instantiate a material point
        MaterialPoint p;

        // Set x position
        x = x_min + col * delta_xy;
        p.getPosition()[0] = x;

        // Set y position
        y = y_max - row * delta_xy;
        p.getPosition()[1] = y;

        // p.getTemperature() = 1.;
        // p.getHeatRate() = 0.;
        material_points.push_back(p);
      }
    }

    for (auto& p : material_points) {
      // std::cout << p << std::endl;
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }
  }

  System system;
  UInt n_points;
  UInt grid_size;
  Real x_min;
  Real x_max;
  Real y_min;
  Real y_max;
  Real x;
  Real y;
  Real delta_xy;
  Real L;
  ComputeTemperature compute_temperature = ComputeTemperature();
};


TEST_F(RandomMaterialPoints, homogeneous_temperature) {
  // Set the volumetric heat source to zero
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);
    mp.setHeatRate(0.);
    mp.setTemperature(1.0);
  }

  // Perform one step of integration
  compute_temperature.compute(system);

  // Verify that the temperature is unchanged
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);
    ASSERT_NEAR(mp.getTemperature(), 1., 1e-10);
  }
}


TEST_F(RandomMaterialPoints, sine_temperature) {
  // Iterate over each point and set the volumetric heat source
  Real heat_rate;
  Real analytical_prediction = 0.;
  for (auto& p: system) {
    // Get the next material point
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Get the position of the point
    x = mp.getPosition()[0];

    // Set the volumetric heat source
    heat_rate = (2. * M_PI / L) * (2. * M_PI / L) * sin(2. * M_PI * x / L);
    mp.setHeatRate(heat_rate);

    // Set the temperature
    analytical_prediction = sin(2. * M_PI * x / L);
    mp.setTemperature(analytical_prediction);
  }

  // Check that the result is stable after one step
  compute_temperature.compute(system);

  // Iteratr over each material point and verify that the temperature matches the analytical prediction
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Get the position of the point
    x = mp.getPosition()[0];

    // Compute the analytical prediction
    analytical_prediction = sin(2. * M_PI * x / L);

    // Verify that the temperature matches the analytical prediction
    ASSERT_NEAR(mp.getTemperature(), analytical_prediction, 1e-10);
  }
}


TEST_F(RandomMaterialPoints, twolines_temperature) {
  // Iterate over each point and set the volumetric heat source
  Real heat_rate = 0.;
  Real analytical_prediction = 0.;
  for (auto& p: system) {
    // Get the next material point
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Get the position of the point
    x = mp.getPosition()[0];

    // Set the volumetric heat source
    if (x == -0.5){
      heat_rate = -1.0;
    }
    else if (x == 0.5){
      heat_rate = 1.0;
    }
    else{
      heat_rate = 0.0;
    }
    mp.setHeatRate(heat_rate);

    // Set the temperature
    if (x <= -0.5){
      analytical_prediction = -x - 1.0;
    }
    else if (x > 0.5){
      analytical_prediction = -x + 1.0;
    }
    else{
      analytical_prediction = x;
    }
    mp.setTemperature(analytical_prediction);
  }

  // Check that the result is stable after one step
  compute_temperature.compute(system);

  // Iterate over each material point and verify that the temperature matches the analytical prediction
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Get the position of the point
    x = mp.getPosition()[0];

    // Compute the analytical prediction
    if (x <= -0.5){
      analytical_prediction = -x - 1.0;
    }
    else if (x > 0.5){
      analytical_prediction = -x + 1.0;
    }
    else{
      analytical_prediction = x;
    }

    // Verify that the temperature matches the analytical prediction
    ASSERT_NEAR(mp.getTemperature(), analytical_prediction, 1e-10);
  }
}
