#ifndef COMPUTE_ARITHMETIC_HH
#define  COMPUTE_ARITHMETIC_HH
#include "series.hh"

class ComputeArithmetic : public Series
{
public:
   double compute(unsigned int N) override;
};
#endif