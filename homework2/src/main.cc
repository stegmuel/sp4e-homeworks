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
#include "parser.hh"
#include <exception>
/* -------------------------------------------------------------------------- */

ArgParser getParser()
{
    ArgParser parser;

    // Define default arguments
    parser.addArgument("serie_type", "arithmetic", {"pi", "arithmetic", "integral"});
    parser.addArgument("integral_f", "cubic", {"cubic", "cos", "sin"});
    parser.addArgument("integral_a", "0");
    parser.addArgument("integral_b", "1");

    return parser;
}

float get_bounds(const std::string bound, std::string bound_name)
{
    if (bound == "pi")
    {
        return M_PI;
    }
    else if (bound == "pi/2")
    {
        return M_PI / 2.0;
    }
    try
    {
        // Try the conversion to float
        float float_bound = std::stof(bound);
        std::cout << "The float value of " << bound_name << " is: " << float_bound << std::endl;
        return float_bound;
    }
    catch (const std::invalid_argument &e)
    {
        // Handle the case where the input is not a valid float
        std::cerr << "Error: Invalid integral bounds - " << e.what() << std::endl;
        exit(1);
    }
}

int main(int argc, char *argv[])
    {
        // Get the parser with default values
        ArgParser parser = getParser();

        // Parse the arguments
        parser.parse(argc, argv);

        // Identify the desired class
        std::string serie_type = parser.get("serie_type");

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
        else
        {
            // Set the function
            std::function<double(double)> f;
            std::string function = parser.get("integral_f");

            // Set the integral bounds
            float a = get_bounds(parser.get("integral_a"), "a");
            float b = get_bounds(parser.get("integral_b"), "b");
            if (function == "cubic")
            {
                f = [](double x)
                { return x * x * x; };
            }
            else if (function == "cos")
            {
                f = [](double x)
                { return cos(x); };
            }
            else if (function == "sin")
            {
                f = [](double x)
                { return sin(x); };
            }
            else
            {
                std::cerr << "The function to integrate must be either of cubic, cos or sin." << std::endl;
                return EXIT_FAILURE;
            }
            serie = std::make_shared<RiemannIntegral>(a, b, f);
        }

        // Compute the serie and print
        double serie_result;
        serie_result = serie->compute(100);
        std::cout << serie_result << std::endl;

        return EXIT_SUCCESS;
    }