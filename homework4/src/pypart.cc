#include <pybind11/pybind11.h>

namespace py = pybind11;

#include "compute.hh"
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
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
      m, "MaterialPointsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // PingPongBallsFactory
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
      m, "PingPongBallsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // PlanetsFactory
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
      m, "PlanetsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

	////////////// CSV ///////////////////
  // CsvWriter
  py::class_<CsvWriter>(
      m, "CsvWriter",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

	////////////// Computes ///////////////////
  // Compute
  py::class_<Compute>(
      m, "Compute",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // ComputeTemperature
  py::class_<ComputeTemperature, Compute>(
      m, "ComputeTemperature",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // ComputeGravity
  py::class_<ComputeGravity, Compute>(
      m, "ComputeGravity",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // ComputeVerletIntegration
  py::class_<ComputeVerletIntegration, Compute>(
      m, "ComputeVerletIntegration",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

}
