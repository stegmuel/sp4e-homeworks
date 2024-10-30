#ifndef COMPUTE_ARITHMETIC_HH
#define COMPUTE_ARITHMETIC_HH
#include "series.hh"

class ComputeArithmetic : public Series
{
protected:
    // Methods
    double computeTerm(unsigned int current_index);

public:
    // Methods
    double getAnalyticPrediction();
};
#endif