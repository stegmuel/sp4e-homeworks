#include "series.cc"
#include "compute_arithmetic.hh"


double ComputeArithmetic::compute(unsigned int N)
{
    double sum = 0.0;
    for (int i=1; i<=N; i++){
        sum += i;
    }
    return sum;
}