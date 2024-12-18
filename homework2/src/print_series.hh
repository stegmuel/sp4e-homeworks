#ifndef PRINT_SERIES_HH
#define PRINT_SERIES_HH
#include "dumper_series.hh"
#include "series.hh"

class PrintSeries : public DumperSeries
{
public:
    // Constructor
    PrintSeries(Series &series, int maxiter, int print_frequency);

    // Methods
    void dump() override;
    void setSeparator(std::string separator) override {};
    std::string getExtension() override { return ""; };

private:
    // Attributes
    int maxiter;
    int print_frequency;
};
#endif