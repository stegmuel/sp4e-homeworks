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
    grid_size = 9;
    for (UInt i = 0; i < grid_size; ++i) {
      for (UInt j = 0; j < grid_size; ++j){
        MaterialPoint p;
        p.getPosition()[0] = Real(j);
        p.getPosition()[1] = Real(i);
        p.getTemperature() = 1.;
        p.getHeatRate() = 0.;
        material_points.push_back(p);
      }
    }

    for (auto& p : material_points) {
      // std::cout << p << std::endl;
      system.addParticle(std::make_shared<MaterialPoint>(p));
    }
  }

  System system;
  UInt grid_size;
  ComputeTemperature compute_temperature = ComputeTemperature();
};


TEST_F(RandomMaterialPoints, homogeneous_temperature) {
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
  Real x_min = -1.;
  Real x_max = 1.;
  Real y_min = -1.;
  Real y_max = 1.;
  Real L = x_max - x_min;
  Real delta = L / grid_size;

  // Iterate over each point and set the volumetric heat source
  for (UInt i = 0; i < grid_size; ++i) {
      for (UInt j = 0; j < grid_size; ++j){
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
        mp.getPosition()[0] = x_min + i * delta;
        mp.getPosition()[1] = y_min + j * delta;
        mp.getHeatRate() = pow(2*M_PI/L, 2)*sin(2*M_PI/L * mp.getPosition()[0]);
        mp.getTemperature() = sin(2*M_PI/L * mp.getPosition()[0]);
      }
  }

  // Check that the result is stable after one step
  compute_temperature.compute(system);

  // Iteratr over each material point and verify that the temperature matches the analytical prediction
  for (UInt i = 0; i < grid_size; ++i) {
      for (UInt j = 0; j < grid_size; ++j){
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
        ASSERT_NEAR(mp.getTemperature(), sin(2*M_PI/L * mp.getPosition()[0]), 1e-3);
      }
  }
}


TEST_F(RandomMaterialPoints, twolines_temperature) {
  // Set the grid attributes
  Real x_min = -1.;
  Real x_max = 1.;
  Real y_min = -1.;
  Real y_max = 1.;
  Real L = x_max - x_min;
  Real delta = L / (grid_size-1);
  
  // Iterate over each point and set the volumetric heat source
  for (UInt i = 0; i < grid_size; ++i) {
      for (UInt j = 0; j < grid_size; ++j){
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
        mp.getPosition()[0] = x_min + i * delta;
        mp.getPosition()[1] = y_min + j * delta;

        // Set Heat Rate
        if (mp.getPosition()[0] == 0.5){
          mp.getHeatRate() = 1.;
        }else if(mp.getPosition()[0] == -0.5){
          mp.getHeatRate() = -1.;
        }else{
          mp.getHeatRate() = 0.;
        }

        // Set Temperature
        if (mp.getPosition()[0] <= -0.5){
          mp.getTemperature() = -mp.getPosition()[0]-1.;
        }else if(mp.getPosition()[0] <= 0.5){
          mp.getTemperature() = mp.getPosition()[0]*1.;
        }else{
          mp.getTemperature() = -mp.getPosition()[0]+1.;
        }
      }
  }

  // Check that the result is stable after one step
  compute_temperature.compute(system);

  // Iteratr over each material point and verify that the temperature matches the analytical prediction
  for (UInt i = 0; i < grid_size; ++i) {
      for (UInt j = 0; j < grid_size; ++j){
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(system.getParticle(j*grid_size+i));
        if (mp.getPosition()[0] <= -0.5){
          ASSERT_NEAR(mp.getTemperature(), -mp.getPosition()[0]-1., 1e-10);
        }else if(mp.getPosition()[0] <= 0.5){
          ASSERT_NEAR(mp.getTemperature(), mp.getPosition()[0]*1., 1e-10);
        }else{
          ASSERT_NEAR(mp.getTemperature(), -mp.getPosition()[0]+1., 1e-10);
        }
        
      }
  }
}