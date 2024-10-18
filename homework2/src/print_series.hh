#ifndef PRINT_SERIES_HH
#define PRINT_SERIES_HH
#include "dumper_series.hh"

class PrintSeries : DumperSeries{
    public:
        PrintSeries(Series &series, int maxiter, int print_frequency);
        void dump() override;

    private:
        int maxiter;
        int print_frequency;
};
#endif