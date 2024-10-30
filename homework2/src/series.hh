#ifndef SERIES_HH
#define SERIES_HH
class Series
{
protected:
    // Methods
    void addTerm();
    virtual double computeTerm(unsigned int current_index) = 0;

    // Attributes
    unsigned int current_index;
    double current_value;

public:
    // Methods
    virtual double compute(unsigned int N);
    virtual double getAnalyticPrediction() = 0;
};
#endif