#include "compute_pi.hh"
#include <cmath>

double ComputePI::compute(unsigned int N)
{
    // Call the compute method from the mother class
    Series::compute(N);
    return sqrt(6. * this->current_value);
}

double ComputePI::getAnalyticPrediction()
{
    return M_PI;
}

double ComputePI::computeTerm(unsigned int current_index)
{
    return 1. / (1. * current_index * current_index);
}