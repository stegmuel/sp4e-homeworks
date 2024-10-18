#include "riemann_integral.hh"
#include <cmath>


double RiemannIntegral::compute(unsigned int N)
{
    double sum = 0.0;
    double delta_x = (this->b - this->a) / N;
    double x_i = this->a;
    for (int i=1; i<=N; i++){
        x_i += delta_x;
        sum += delta_x * this->f(x_i);
    }
    return sum;
}


double RiemannIntegral::computeTerm(unsigned int current_index)
{
    return std::nan("");
}


double RiemannIntegral::getAnalyticPrediction()
{
    return std::nan("");
}