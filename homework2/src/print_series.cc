#include "dumper_series.cc"
#include "print_series.hh"
#include <iostream>


PrintSeries::PrintSeries(Series &series, int maxiter, int print_frequency):
    DumperSeries::DumperSeries(series),maxiter(maxiter), print_frequency(print_frequency){}


void PrintSeries::dump(){
    for (int i=1; i<=int(maxiter/print_frequency); i++){
        double value = series.compute(i*print_frequency);
            std::cout << i << std::scientific << value << "\n";
    } // end for loop
}