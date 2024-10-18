#ifndef COMPUTE_PI_HH
#define  COMPUTE_PI_HH
#include "series.hh"

class ComputePI : public Series
{
public:
    double compute(unsigned int N) override;
    double getAnalyticPrediction() override;
};
#endif