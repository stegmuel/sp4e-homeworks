#include "compute_arithmetic.hh"

double ComputeArithmetic::computeTerm(unsigned int current_index)
{
    return 1. * current_index;
}

double ComputeArithmetic::getAnalyticPrediction()
{
    return 1. * this->current_index * (this->current_index + 1.0) / 2.0;
}