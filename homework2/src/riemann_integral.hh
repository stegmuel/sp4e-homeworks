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

public:
    RiemannIntegral(double a, double b, std::function<double(double)> f)
    {
        this->a = a;
        this->b = b;
        this->f = f;
    }
    virtual double compute(unsigned int N);
};
#endif