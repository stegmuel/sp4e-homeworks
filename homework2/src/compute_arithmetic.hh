#ifndef COMPUTE_ARITHMETIC_HH
#define  COMPUTE_ARITHMETIC_HH
#include "series.hh"

class ComputeArithmetic : public Series
{
protected:
    double computeTerm(unsigned int current_index);
public:
    double getAnalyticPrediction();
    // ComputeArithmetic();
    // virtual ~ComputeArithmetic();
    // virtual double compute(unsigned int N);
};
#endif