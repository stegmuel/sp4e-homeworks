#include "series.hh"
#include <cmath>

double Series::getAnalyticPrediction()
{
    return std::nan("");
}

void Series::addTerm()
{
    this->current_index++;
    this->current_value += this->computeTerm(this->current_index);
}


double Series::compute(unsigned int N)
{
    // Check if part of the serie is already computed
    if (this->current_index <= N)
    {
        // Update the remaining number of terms to compute
        N -= this->current_index;
    }
    else
    {
        // Start from the begining -> resest current term/value
        this->current_index = 0;
        this->current_value = 0.0;
    }

    // Iterate over the remaining terms
    for (int k = 0; k < N; k++)
    {
        this->addTerm();
    }

    // Return the current value
    return this->current_value;
}