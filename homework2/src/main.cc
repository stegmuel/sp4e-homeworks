#include <cstdlib>
#include <iostream>
#include "compute_arithmetic.hh"
/* -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    // Instantiate an arithmetic serie
    ComputeArithmetic computer;

    // Compute the sum and print
    double sum;
    sum = computer.compute(10);
    std::cout << sum << std::endl;

    return EXIT_SUCCESS;
}