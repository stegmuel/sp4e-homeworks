#ifndef DUMPER_SERIES_HH
#define DUMPER_SERIES_HH
#include "series.hh"
#include <string>

class DumperSeries
{
public:
    DumperSeries(Series &series);
    virtual void dump() = 0;
    virtual void dump(std::ostream &os);
    virtual void setSeparator(std::string) = 0;
    virtual void setPrecision(unsigned int precision);
    virtual std::string getExtension() = 0;

protected:
    int maxiter = 100;
    int print_frequency = 10;
    std::string separator = " ";
    int precision = 6;
    Series &series;
};
inline std::ostream &operator<<(std::ostream &stream, DumperSeries &_this)
{
    _this.dump(stream);
    return stream;
}
#endif