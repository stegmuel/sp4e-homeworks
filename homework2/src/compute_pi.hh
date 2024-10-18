#ifndef COMPUTE_PI_HH
#define  COMPUTE_PI_HH
#include "series.hh"

class ComputePI : public Series
{
protected:
    double computeTerm(unsigned int current_index);
public:
    // ComputeArithmetic();
    // virtual ~ComputeArithmetic();
    virtual double compute(unsigned int N);
    virtual double getAnalyticPrediction();
};
#endif