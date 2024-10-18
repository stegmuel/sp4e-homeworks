#ifndef COMPUTE_ARITHMETIC_HH
#define  COMPUTE_ARITHMETIC_HH

class ComputeArithmetic : public Series
{
public:
   double compute(unsigned int N) override;
};
#endif