#ifndef COMPUTE_PI_HH
#define  COMPUTE_PI_HH
#include "series.hh"

class ComputePI : public Series
{
public:
    // ComputeArithmetic();
    // virtual ~ComputeArithmetic();
    virtual double compute(unsigned int N);
};
#endif