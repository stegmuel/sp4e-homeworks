#include "compute_temperature.hh"
#include "csv_reader.hh"
#include "csv_writer.hh"
#include "material_point.hh"
#include "material_points_factory.hh"
#include "system.hh"
#include <gtest/gtest.h>
#include <vector>
#include "vector.hh"


class ComputeTemperatureHomogeneous : public ::testing::Test {
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
};


TEST_F(ComputeTemperatureHomogeneous, homogeneous_temperature) {
    ComputeTemperature ct = ComputeTemperature();
    ct.compute(system);

    for (auto& p: system) {
        MaterialPoint& mp = dynamic_cast<MaterialPoint&>(p);
        ASSERT_NEAR(mp.getTemperature(), 1., 1e-10);
    }

}
