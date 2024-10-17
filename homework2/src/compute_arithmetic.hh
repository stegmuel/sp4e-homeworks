#ifndef COMPUTE_ARITHMETIC_HH
#define  COMPUTE_ARITHMETIC_HH
#include "series.hh"

class ComputeArithmetic : public Series
{
public:
    // ComputeArithmetic();
    // virtual ~ComputeArithmetic();
    virtual double compute(unsigned int N);
};
#endif