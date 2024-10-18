#ifndef SERIES_HH
#define SERIES_HH
class Series
{
protected:
    unsigned int current_index;
    double current_value;
    void addTerm();
    virtual double computeTerm(unsigned int current_index) = 0;

public:
    virtual double compute(unsigned int N);
    virtual double getAnalyticPrediction() = 0;
};
#endif