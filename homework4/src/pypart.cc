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
#include "compute_interaction.hh"


PYBIND11_MODULE(pypart, m) {

  m.doc() = "pybind of the Particles project";

	////////////// Factories ///////////////////
  // ParticlesFactoryInterface
  py::class_<ParticlesFactoryInterface>(
      m, "ParticlesFactoryInterface",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
	// Expose the static getInstance() method
	.def_static("getInstance", &ParticlesFactoryInterface::getInstance,
	            py::return_value_policy::reference,
	            "Get the singleton instance of the particles factory.")
	.def("createSimulation", 
	    [](ParticlesFactoryInterface &self, const std::string &fname, Real timestep) -> SystemEvolution& {
	        // Direct call to the base createSimulation method (non-templated)
	        return self.createSimulation(fname, timestep);
	    },
	    py::return_value_policy::reference_internal,
	    py::arg("fname"), py::arg("timestep")
	)
	.def("createSimulation", 
	    py::overload_cast<const std::string&, Real, py::function>(&ParticlesFactoryInterface::createSimulation<py::function>),
	    py::return_value_policy::reference_internal,
	    py::arg("fname"), py::arg("timestep"), py::arg("func")
	)
  .def_property_readonly(
      "system_evolution", 
      &ParticlesFactoryInterface::getSystemEvolution, 
      // Tie lifetime to ParticlesFactoryInterface
      py::return_value_policy::reference_internal,
      "Access the system evolution instance"
  );
	 
  // MaterialPointsFactory
  py::class_<MaterialPointsFactory, ParticlesFactoryInterface>(
      m, "MaterialPointsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
  // Expose the static getInstance() method
  .def_static("getInstance", &MaterialPointsFactory::getInstance,
      py::return_value_policy::reference,
      "Get the singleton instance of PlanetsFactory.");

  // PingPongBallsFactory
  py::class_<PingPongBallsFactory, ParticlesFactoryInterface>(
      m, "PingPongBallsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // PlanetsFactory
  py::class_<PlanetsFactory, ParticlesFactoryInterface>(
      m, "PlanetsFactory",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
	// Expose the static getInstance() method
	.def_static("getInstance", &PlanetsFactory::getInstance,
	            py::return_value_policy::reference,
	            "Get the singleton instance of PlanetsFactory.");

	////////////// CSV ///////////////////
  // CsvWriter
  py::class_<CsvWriter>(
      m, "CsvWriter",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
  // Constructor
  .def(py::init<const std::string &>(),
       py::arg("filename"),            
       "Constructor for CsvWriter.")
  .def("write", &CsvWriter::write,
      py::arg("system"),
      "Writes the state of the given system to the CSV file.");

	////////////// Computes ///////////////////
  // Compute
  py::class_<Compute, std::shared_ptr<Compute>>(
      m, "Compute",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // ComputeInteraction
  py::class_<ComputeInteraction, Compute, std::shared_ptr<ComputeInteraction>>(
      m, "ComputeInteraction",
      py::dynamic_attr() // to allow new members to be created dynamically
  );

  // ComputeTemperature
  py::class_<ComputeTemperature, Compute, std::shared_ptr<ComputeTemperature>>(
      m, "ComputeTemperature",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
  // Constructor
	.def(py::init<>(), "Constructor for ComputeTemperature")
  // Setters and getters for the attributes of ComputeTemperature
  .def_property("conductivity", 
      // Getter for the conductivity
      [](ComputeTemperature &self) -> Real& { return self.getConductivity(); },
      // Setter for the conductivity
      [](ComputeTemperature &self, Real value) { self.getConductivity() = value; },
      "Heat conductivity of the material.")
  .def_property("capacity", 
      // Getter for the capacity
      [](ComputeTemperature &self) -> Real& { return self.getCapacity(); },
      // Setter for the capacity
      [](ComputeTemperature &self, Real value) { self.getCapacity() = value; },
      "Heat capacity of the material.")
  .def_property("density", 
      // Getter for the density
      [](ComputeTemperature &self) -> Real& { return self.getDensity(); },
      // Setter of the density
      [](ComputeTemperature &self, Real value) { self.getDensity() = value; },
      "Density of the material.")
  .def_property("L", 
      // Getter for L
      [](ComputeTemperature &self) -> Real& { return self.getL(); },
      // Setter for L
      [](ComputeTemperature &self, Real value) { self.getL() = value; },
      "Characteristic length of the square.")
  .def_property("deltat", 
      // Getter for Deltat
      [](ComputeTemperature &self) -> Real& { return self.getDeltat(); }, 
      // Setter for Delta
      [](ComputeTemperature &self, Real value) { self.getDeltat() = value; },
      "Time step size for the simulation.");

  // ComputeGravity
  py::class_<ComputeGravity, ComputeInteraction, std::shared_ptr<ComputeGravity>>(
      m, "ComputeGravity",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
	// Constructor
	.def(py::init<>(), "Constructor for ComputeGravity")
	// Set the gravitational constant G
  .def("setG", &ComputeGravity::setG, py::arg("G"),
       "Set the gravitational constant G.") ;

  // ComputeVerletIntegration
  py::class_<ComputeVerletIntegration, Compute, std::shared_ptr<ComputeVerletIntegration>>(
      m, "ComputeVerletIntegration",
      py::dynamic_attr() // to allow new members to be created dynamically
  )
	// Constructor
  .def(py::init<Real>(), py::arg("timestep"),
       "Constructor that initializes the object with a timestep.")
	// Add an interaction to the simulation
  .def("addInteraction", &ComputeVerletIntegration::addInteraction, py::arg("interaction"),
       "Add an interaction to the simulation.");

	///////////// SystemEvolution ///////////////////
  // SystemEvolution
  py::class_<SystemEvolution>(
    m, "SystemEvolution",
    py::dynamic_attr() // to allow new members to be created dynamically
  )
  .def("addCompute", &SystemEvolution::addCompute)
  .def("getSystem", &SystemEvolution::getSystem,
      // Lifetime tied to SystemEvolution
      py::return_value_policy::reference_internal,
      "Get the system object.")
  .def("setNSteps", &SystemEvolution::setNSteps,
      py::arg("nsteps"),
      "Set the number of steps for the simulation.")
  .def("setDumpFreq", &SystemEvolution::setDumpFreq,
      py::arg("freq"),
      "Set the writing frequency for the simulation.")
  .def("evolve", &SystemEvolution::evolve,
      "Launcher for the simulation.") ;

	///////////// System ///////////////////
  py::class_<System>(
    m, "System",
    py::dynamic_attr() // to allow new members to be created dynamically
  );
}
