#include "dumper_series.hh"
#include "write_series.hh"
#include <cmath>
#include <fstream>
#include <iomanip>

WriteSeries::WriteSeries(Series &series, int maxiter, int print_frequency) : DumperSeries::DumperSeries(series), maxiter(maxiter), print_frequency(print_frequency) {}

void WriteSeries::setSeparator(std::string separator)
{
    this->separator = separator;
}

void WriteSeries::dump()
{
    // Prepare the proper filename
    std::string filename = "series.txt";
    if (this->separator == ",")
    {
        filename = "series.csv";
    }
    else if (this->separator == "|")
    {
        filename = "series.psv";
    }

    // Open the file
    std::ofstream f(filename);

    // Call the base class method
    DumperSeries::dump(f);

    // Close the file
    f.close();
}