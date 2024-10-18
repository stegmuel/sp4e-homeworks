#include "dumper_series.hh"
#include "print_series.hh"
#include <iostream>
#include <cmath>


PrintSeries::PrintSeries(Series &series, int maxiter, int print_frequency):
    DumperSeries::DumperSeries(series),maxiter(maxiter), print_frequency(print_frequency){}


void PrintSeries::dump(){
    for (int i=1; i<=int(maxiter/print_frequency); i++){
        int n = i*print_frequency;
        double value = series.compute(n);
        double anlt_pred = series.getAnalyticPrediction();
        std::cout << n << " " << std::scientific << value;
        if (!std::isnan(anlt_pred)){
            double diff = fabs(anlt_pred - value);
            std::cout << " " << diff;
        }
        std::cout << std::endl;
    } // end for loop
}