#ifndef DUMPER_SERIES_HH
#define DUMPER_SERIES_HH
#include "series.hh"

class DumperSeries{
    public:
        DumperSeries(Series &series);
        virtual void dump() = 0;

    protected:
        Series &series;
};
#endif