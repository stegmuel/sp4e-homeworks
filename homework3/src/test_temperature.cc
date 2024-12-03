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
    MaterialPointsFactory::getInstance();
    std::vector<MaterialPoint> material_points;
    n_points = 9;
    for (UInt i = 0; i < n_points; ++i) {
      MaterialPoint p;
      p.getPosition() = i;
      p.getTemperature() = 1.;
      p.getHeatRate() = 0.;
      material_points.push_back(p);
    }

    for (auto& p : material_points) {
      // std::cout << p << std::endl;
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }
  }

  System system;
  UInt n_points;
  ComputeTemperature compute_temperature = ComputeTemperature();
};


TEST_F(RandomMaterialPoints, homogeneous_temperature) {
  // Set the volumetric heat source to zero
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);
    mp.setHeatRate(0.);
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
  // Set the grid attributes
  UInt grid_size = sqrt(n_points);
  Real x_min = -1.;
  Real y_min = -1.;
  Real x_max = 1.;
  Real y_max = 1.;
  Real x = x_min;
  Real y = y_min;
  Real L = x_max - x_min;
  Real delta_x = L / (grid_size - 1);
  // Real delta_y = (y_max - y_min) / (grid_size - 1);
  UInt row = 0;
  UInt col = 0;
  Real heat_rate = 0.;

  // Iterate over each point and set the volumetric heat source
  size_t mp_counter = 0;
  for (auto& p: system) {
    // Get the next material point
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Infer the position of the point
    // row = mp_counter / grid_size;
    col = mp_counter % grid_size;
    x = x_min + col * delta_x;
    // y = y_min + row * delta_y;

    // Set the volumetric heat source
    heat_rate = (2. * M_PI / L) * (2. * M_PI / L) * sin(2. * M_PI * x / L);
    mp.setHeatRate(heat_rate);

    // Update the material points counter
    mp_counter += 1;
  }

  // Wait until equilibrium
  for (size_t i = 0; i < 1000; i++)
  {
    compute_temperature.compute(system);
  }
  

  // Iteratr over each material point and verify that the temperature matches the analytical prediction
  mp_counter = 0;
  Real analytical_prediction = 0.;
  for (auto& p: system) {
    MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);

    // Infer the position of the point
    col = mp_counter % grid_size;
    x = x_min + col * delta_x;

    // Compute the analytical prediction
    analytical_prediction = sin(2. * M_PI * x / L);

    // Verify that the temperature matches the analytical prediction
    ASSERT_NEAR(mp.getTemperature(), analytical_prediction, 1e-1);

    // Update the material points counter
    mp_counter += 1;
  }
}