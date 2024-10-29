#ifndef WRITE_SERIES_HH
#define WRITE_SERIES_HH
#include "dumper_series.hh"
#include "series.hh"

class WriteSeries : public DumperSeries
{
public:
    WriteSeries(Series &series, int maxiter, int print_frequency);
    void dump() override;
    void setSeparator(std::string separator);
    std::string getExtension() { return this->extension; }

protected:
    int maxiter;
    int print_frequency;
    std::string extension = "txt";
    void setExtension(std::string separator);
};
#endif