#include "dumper_series.hh"
#include "write_series.hh"
#include <cmath>
#include <fstream>
#include <iomanip>

WriteSeries::WriteSeries(Series &series, int maxiter, int print_frequency) : DumperSeries::DumperSeries(series), maxiter(maxiter), print_frequency(print_frequency) {}

void WriteSeries::setSeparator(std::string separator)
{
    // Set the separator
    this->separator = separator;

    // Set the extension accordingly
    this->setExtension(separator);
}

void WriteSeries::setExtension(std::string separator){
    if (separator == ",")
    {
        this->extension = "csv";
    }
    else if (separator == "|")
    {
        this->extension = "psv";
    }
}

void WriteSeries::dump()
{
    // Prepare the proper filename
    std::string filename = "series." + this->extension;

    // Open the file
    std::ofstream f(filename);

    // Call the base class method
    DumperSeries::dump(f);

    // Close the file
    f.close();
}