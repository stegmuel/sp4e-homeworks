#include <iostream>
#include "parser.hh"

void ArgParser::addArgument(const std::string &name, const std::string &defaultValue, std::set<std::string> validValues)
{
    // Set values
    this->args[name] = defaultValue;

    // If the set of potential values if provided
    if (!validValues.empty())
    {
        this->validArgs[name] = validValues;
    }
}

void ArgParser::parse(int argc, char *argv[])
{
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if (arg.find("--") == 0)
        {
            // Remove "--"
            std::string name = arg.substr(2);
            if (i + 1 < argc)
            {
                // Get the value
                std::string value = argv[++i];

                // Check if the value is valid when the set of accepted values is provided
                if (validArgs.find(name) != validArgs.end())
                {
                    if (validArgs[name].find(value) == validArgs[name].end())
                    {
                        std::cerr << "Error: Invalid value '" << value
                                  << "' for argument --" << name << ".\n";
                        std::cerr << "Accepted values are: ";
                        for (const auto &v : validArgs[name])
                            std::cerr << v << " ";
                        std::cerr << std::endl;
                        exit(1); // Exit on error
                    }
                }
                this->args[name] = value;
            }
            else
            {
                std::cerr << "Warning: Argument " << name << " expects a value." << std::endl;
            }
        }
    }
}

std::string ArgParser::get(const std::string &name)
{
    // Return the queries value
    return this->args[name];
}