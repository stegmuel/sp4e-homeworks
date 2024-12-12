#include "compute_temperature_finite_differences.hh"
#include "material_point.hh"
#include "matrix.hh"

void ComputeTemperatureFiniteDifferences::compute(System& system) {
  static bool should_factorize = true;

  if (should_factorize) {
    assembleLinearOperator(system);
    A.makeCompressed();
    solver->analyzePattern(A);
    solver->factorize(A);

    should_factorize = false;
  }

  auto N = system.getNbParticles();

  Eigen::VectorXd theta(N);

  assembleRightHandSide(system);
  theta = solver->solve(rhs);

  // Transferring temperature back
  auto it = theta.begin();
  for (auto& part : system) {
    static_cast<MaterialPoint&>(part).getTemperature() = (*it);
    ++it;
  }
}

void ComputeTemperatureFiniteDifferences::assembleLinearOperator(
    System& system) {}

void ComputeTemperatureFiniteDifferences::assembleRightHandSide(
    System& system) {}
