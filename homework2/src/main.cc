#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "print_series.hh"
#include "write_series.hh"
/* -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    // Read arguments
    if (argc != 2){
        std::cerr << "missing arguments" << std::endl;
        return EXIT_FAILURE;
    }
    std::string series_name = std::string(argv[1]);
    int N = 10;
    int maxiter = 50;
    int print_frequency = 10;

    // Instantiate the series asked by the user
    Series *ptr_series;
    if (series_name == "pi"){
        ComputePI series;
        ptr_series = &series;
    }
    else if (series_name == "arithmetic"){
        ComputeArithmetic series;
        ptr_series = &series;
    }
    else{
        std::cerr << "Specified series not implemented " << std::endl;
        return EXIT_FAILURE;
    }

    // PrintSeries printer = PrintSeries(*ptr_series, maxiter, print_frequency);
    // printer.dump();
    WriteSeries printer = WriteSeries(*ptr_series, maxiter, print_frequency);
    printer.dump();

    return EXIT_SUCCESS;
}