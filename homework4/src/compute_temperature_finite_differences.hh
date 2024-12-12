#ifndef COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH
#define COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH

#include "compute.hh"
#include <Eigen/SparseCore>
#include <Eigen/SparseLU>

class ComputeTemperatureFiniteDifferences : public Compute {
public:
  using SparseMatrix = Eigen::SparseMatrix<Real, Eigen::ColMajor>;
  using Solver = Eigen::SparseLU<SparseMatrix>;

  ComputeTemperatureFiniteDifferences(Real dt) : dt(dt) {
    solver = std::make_shared<Solver>();
  };

  void compute(System& system) override;
  void assembleLinearOperator(System& system);
  void assembleRightHandSide(System& system);

protected:
  Real dt;
  Eigen::VectorXd rhs;
  SparseMatrix A;
  std::shared_ptr<Solver> solver;
};

#endif  // COMPUTE_TEMPERATURE_FINITE_DIFFERENCES_HH
