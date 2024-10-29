#include "dumper_series.hh"
#include "print_series.hh"
#include <iostream>
#include <cmath>
#include <iomanip>

// Constructor
PrintSeries::PrintSeries(Series &series, int maxiter, int print_frequency) : DumperSeries(series, maxiter, print_frequency) {}

void PrintSeries::dump()
{
    // Call the base class method
    DumperSeries::dump(std::cout);
}
