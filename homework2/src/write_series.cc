#include "dumper_series.hh"
#include "write_series.hh"
#include <cmath>
#include <fstream>


WriteSeries::WriteSeries(Series &series, int maxiter, int print_frequency):
    DumperSeries::DumperSeries(series),maxiter(maxiter), print_frequency(print_frequency){}


void WriteSeries::dump(){
    std::ofstream f("out.txt");
    for (int i=1; i<=int(maxiter/print_frequency); i++){
        int n = i*print_frequency;
        double value = series.compute(n);
        double anlt_pred = series.getAnalyticPrediction();
        f << n << " " << std::scientific << value;
        if (!std::isnan(anlt_pred)){
            double diff = fabs(anlt_pred - value);
            f << " (" << diff << ")";
        }
        f << std::endl;
    } // end for loop
}