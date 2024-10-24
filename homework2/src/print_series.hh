#ifndef PRINT_SERIES_HH
#define PRINT_SERIES_HH
#include "dumper_series.hh"
#include "series.hh"

class PrintSeries : public DumperSeries
{
public:
    PrintSeries(Series &series, int maxiter, int print_frequency);
    void dump() override;
    void setSeparator(std::string separator) override {} ;

private:
    int maxiter;
    int print_frequency;
};
#endif