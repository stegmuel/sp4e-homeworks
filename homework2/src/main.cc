#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include "series.hh"
#include "compute_arithmetic.hh"
#include "compute_pi.hh"
#include "riemann_integral.hh"
#include <memory>
#include <functional>
#include <cmath>
/* -------------------------------------------------------------------------- */

int main(int argc, char **argv)
{
    // Arguments to be parsed
    std::string serie_type;
    std::string function = "cos";
    float a = 0.0;
    float b = 1.0;

    // Parse the arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];

        if (arg == "-s" || arg == "--serie_type")
        {
            // Check if next argument exists
            if (i + 1 < argc)
            {
                // Check if the choice is valid
                if (std::string(argv[i + 1]) != "pi" && std::string(argv[i + 1]) != "arithmetic" && std::string(argv[i + 1]) != "integral")
                {
                    std::cerr << argv[i + 1] << " is not a valid option for argument serie_type." << std::endl;
                    return EXIT_FAILURE;
                }
                else
                {
                    // Store the type of serie to compute
                    serie_type = argv[++i];
                }
            }
            else
            {
                std::cerr << "--serie_type option requires one argument." << std::endl;
                return EXIT_FAILURE;
            }
        }
        else
        {
            std::cerr << "Unknown argument: " << arg << std::endl;
            return EXIT_FAILURE;
        }
    }

    // Instantiate the desired class
    std::shared_ptr<Series> serie = nullptr;
    if (serie_type == "pi")
    {
        // Instantiate a PI serie
        serie = std::make_shared<ComputePI>();
    }
    else if (serie_type == "arithmetic")
    {
        // Instantiate an arithmetic serie
        serie = std::make_shared<ComputeArithmetic>();
    }
    else {
        // Define the function
        std::function<double(double)> f;
        if (function == "x**3") {
            f = [](double x) { return x * x * x; };
        }
        else if (function == "cos"){
            f = [](double x) { return cos(x); };
        }
        else if (function == "sin"){
            f = [](double x) { return sin(x); };
        }
        else{
            std::cerr << "The function to integrate must be either of x**3, cos(x) or sin(x)." << std::endl;
            return EXIT_FAILURE;
        }
        serie = std::make_shared<RiemannIntegral>(a, b, f);
    }

    // Compute the serie and print
    double serie_result;
    serie_result = serie->compute(10);
    std::cout << serie_result << std::endl;

    return EXIT_SUCCESS;
}