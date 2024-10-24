#include <iostream>
#include "parser.hh"


void ArgParser::addArgument(const std::string &name, const std::string &defaultValue)
{
    // Set values
    this->args[name] = defaultValue;
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
                // Store the value
                this->args[name] = argv[++i]; 
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