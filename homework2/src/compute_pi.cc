#include "compute_pi.hh"
#include <cmath>


double ComputePI::compute(unsigned int N)
{
    double sum = 0.0;
    for (int i=N; i>=1; i--){
        sum += 1. / (i * i);
    }
    sum = sqrt(6. * sum);
    return sum;
}