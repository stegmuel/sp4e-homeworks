#ifndef RIEMANN_INTEGRAL_HH
#define RIEMANN_INTEGRAL_HH
#include "series.hh"
#include <functional>

class RiemannIntegral : public Series
{
protected:
    // Methods
    double computeTerm(unsigned int current_index);

    // Attributes
    double a;
    double b;
    std::function<double(double)> f;

public:
    // Constructor
    RiemannIntegral(double a, double b, std::function<double(double)> f)
    {
        this->a = a;
        this->b = b;
        this->f = f;
    }

    // Methods
    double compute(unsigned int N);
    double getAnalyticPrediction();
};
#endif