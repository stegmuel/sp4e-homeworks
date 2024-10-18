#ifndef RIEMANN_INTEGRAL_HH
#define RIEMANN_INTEGRAL_HH
#include "series.hh"
#include <functional>

class RiemannIntegral : public Series
{
protected:
    double a;
    double b;
    std::function<double(double)> f;
    double computeTerm(unsigned int current_index);

public:
    RiemannIntegral(double a, double b, std::function<double(double)> f)
    {
        this->a = a;
        this->b = b;
        this->f = f;
    }
    double compute(unsigned int N);
    double getAnalyticPrediction();
};
#endif