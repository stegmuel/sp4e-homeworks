#include "dumper_series.hh"
#include <cmath>
#include <iomanip>

DumperSeries::DumperSeries(Series &series) : series(series) {};

void DumperSeries::setPrecision(unsigned int precision)
{
    this->precision = precision;
}

void DumperSeries::dump(std::ostream &os)
{
    // Set the precision
    os << std::setprecision(this->precision);

    // Iterate over the serie
    for (int i = 1; i <= int(maxiter / print_frequency); i++)
    {
        int n = i * print_frequency;
        double value = series.compute(n);
        double anlt_pred = series.getAnalyticPrediction();
        os << n << separator << std::scientific << value;
        if (!std::isnan(anlt_pred))
        {
            double diff = fabs(anlt_pred - value);
            os << separator << std::scientific << diff;
        }
        else
        {
            os << separator << nan("");
        }
        os << std::endl;
    } // end for loop
}