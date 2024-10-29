#ifndef WRITE_SERIES_HH
#define WRITE_SERIES_HH
#include "dumper_series.hh"
#include "series.hh"

class WriteSeries : public DumperSeries
{
public:
    // Constructor
    WriteSeries(Series &series, int maxiter, int print_frequency);

    // Methods
    void dump() override;
    void setSeparator(std::string separator);
    std::string getExtension() { return this->extension; }

protected:
    // Methods
    void setExtension(std::string separator);

    // Attributes
    int maxiter;
    int print_frequency;
    std::string extension = "txt";
};
#endif