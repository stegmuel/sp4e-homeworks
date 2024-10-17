#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
/* -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    // Instantiate an arithmetic serie
    ComputeArithmetic computer;

    // Compute the sum and print
    double sum;
    sum = computer.compute(10);
    std::cout << sum << std::endl;

    // Instantiate a PI serie
    ComputePI pi_computer;

    // Compute the sum and print
    double pi;
    pi = pi_computer.compute(1000);
    std::cout << pi << std::endl;

    return EXIT_SUCCESS;
}