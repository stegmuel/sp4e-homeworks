#include "compute_temperature_finite_differences.hh"
#include "csv_writer.hh"
#include "fft.hh"
#include "material_points_factory.hh"
#include "my_types.hh"
#include "vector.hh"
#include <gtest/gtest.h>

template <typename F1, typename F2>
System createSystem(UInt N, F1 temperature_functor, F2 heat_source_functor) {
  auto& factory = MaterialPointsFactory::getInstance();
  System system;

  for (UInt i = 0; i < N; ++i) {
    for (UInt j = 0; j < N; ++j) {
      // create particle
      auto p = factory.createParticle();
      auto& part = static_cast<MaterialPoint&>(*p);

      auto x = -1. + 2. * double(i) / N;
      auto y = -1. + 2. * double(j) / N;
      auto& pos = part.getPosition();
      pos[0] = x;
      pos[1] = y;
      pos[2] = 0;

      auto& temp = part.getTemperature();
      temp = temperature_functor(i, j, pos);
      auto& heat_source = part.getHeatSource();
      heat_source = heat_source_functor(i, j, pos);

      // add particle to system
      system.addParticle(std::move(p));
    }
  }
  return system;
}

TEST(ComputeTemperatureFiniteDifferences, heat_source_lines) {
  auto& factory = MaterialPointsFactory::getInstance();
  UInt N = 256;

  auto system = createSystem(
      N,
      [](UInt i, UInt j, auto& pos) {
        if (pos[0] <= -1. / 2.)
          return -pos[0] - 1.;
        else if (pos[0] > 1. / 2.)
          return -pos[0] + 1.;
        else
          return pos[0];
      },
      [&](UInt i, UInt j, auto& pos) {
        if (i == int(double(N) / 4.))
          return -double(N);
        if (i == int(3. * double(N) / 4.))
          return double(N);
        return 0.;
      });

  ComputeTemperatureFiniteDifferences compute(1.);

  // launch it twice since the analytical solution do
  // not account for discretization
  compute.compute(system);
  compute.compute(system);

  for (auto&& p : system) {
    auto& part = static_cast<MaterialPoint&>(p);
    ASSERT_NEAR(part.getTemperatureRate(), 0., 1e-5);
  }
}

TEST(ComputeTemperatureFiniteDifferences, constant_temperature) {
  auto& factory = MaterialPointsFactory::getInstance();
  UInt N = 256;
  auto system = createSystem(
      N, [&](UInt i, UInt j, auto& pos) { return 1.; },
      [&](UInt i, UInt j, auto& pos) { return 0.; });

  ComputeTemperatureFiniteDifferences compute(1.);

  // launch it twice since the analytical solution do not account for
  // discretization
  compute.compute(system);
  compute.compute(system);

  for (auto&& p : system) {
    auto& part = static_cast<MaterialPoint&>(p);
    ASSERT_NEAR(part.getTemperatureRate(), 0., 1e-10);
  }
}
