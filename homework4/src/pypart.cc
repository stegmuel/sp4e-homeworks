#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute_gravity.hh"
#include "compute_temperature.hh"
#include "compute_verlet_integration.hh"
#include "csv_writer.hh"
#include "material_points_factory.hh"
#include "ping_pong_balls_factory.hh"
#include "planets_factory.hh"

PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";

	////////////// Factories ///////////////////
  // ParticlesFactoryInterface
  py::class_<ParticlesFactoryInterface>(
      m, "ParticlesFactoryInterface",
      py::dynamic_attr() // to allow new members to be created dynamically
  );
	 
  // MaterialPointsFactory
  py::class_<MaterialPointsFactory>(
      m, "MaterialPointsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // PingPongBallsFactory
  py::class_<PingPongBallsFactory>(
      m, "PingPongBallsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // PlanetsFactory
  py::class_<PlanetsFactory>(
      m, "PlanetsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

	////////////// CSV ///////////////////
}
