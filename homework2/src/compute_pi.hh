#ifndef COMPUTE_PI_HH
#define COMPUTE_PI_HH
#include "series.hh"

class ComputePI : public Series
{
protected:
    double computeTerm(unsigned int current_index) override;

public:
    // ComputeArithmetic();
    // virtual ~ComputeArithmetic();
    double compute(unsigned int N) override;
    double getAnalyticPrediction();
};
#endif