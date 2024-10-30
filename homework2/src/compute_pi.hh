#ifndef COMPUTE_PI_HH
#define COMPUTE_PI_HH
#include "series.hh"

class ComputePI : public Series
{
protected:
    // Methods
    double computeTerm(unsigned int current_index) override;

public:
    // Methods
    double compute(unsigned int N) override;
    double getAnalyticPrediction();
};
#endif