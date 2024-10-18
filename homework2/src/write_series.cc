#include "dumper_series.hh"
#include "write_series.hh"
#include <cmath>
#include <fstream>


WriteSeries::WriteSeries(Series &series, int maxiter, int print_frequency):
    DumperSeries::DumperSeries(series),maxiter(maxiter), print_frequency(print_frequency){}

void WriteSeries::setSeparator(char separator){
    this->separator = separator;
}


void WriteSeries::dump(){
    std::string filename = "series.txt";
    if (this->separator == ','){
        filename = "series.csv";
    }
    else if (this->separator == '|'){
        filename = "series.psv";
    }
        
    std::ofstream f(filename);
    for (int i=1; i<=int(maxiter/print_frequency); i++){
        int n = i*print_frequency;
        double value = series.compute(n);
        double anlt_pred = series.getAnalyticPrediction();
        f << n << separator << std::scientific << value;
        if (!std::isnan(anlt_pred)){
            double diff = fabs(anlt_pred - value);
            f << separator << std::scientific << diff;
        }
        else{
            f << separator << nan("");
        }
        f << std::endl;
    } // end for loop
}