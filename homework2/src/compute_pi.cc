#include "compute_pi.hh"
#include "math.h"


double ComputePI::compute(unsigned int N)
{
    double sum = 0.0;
    for (int i=N; i>=1; i--){
        sum += 1. / (i * i);
    }
    sum = sqrt(6. * sum);
    return sum;
}

double ComputePI::getAnalyticPrediction(){
    return M_PI;
}