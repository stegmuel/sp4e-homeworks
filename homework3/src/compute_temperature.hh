#ifndef __COMPUTE_TEMPERATURE__HH__
#define __COMPUTE_TEMPERATURE__HH__

/* -------------------------------------------------------------------------- */
#include "compute.hh"

//! Compute contact interaction between ping-pong balls
class ComputeTemperature : public Compute {

  // Virtual implementation
public:
  //! Penalty contact implementation
  void compute(System& system) override;

private:
  // Add compute specific attribute
  Real rho = 1.0;
  Real capacity = 1.0;
  Real kappa = 1.0;
  Real delta_t = 1.0;

};

/* -------------------------------------------------------------------------- */
#endif  //__COMPUTE_TEMPERATURE__HH__
