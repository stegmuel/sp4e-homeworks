#ifndef PARSER_HH
#define PARSER_HH
#include <map>
#include <string>
#include <set>

class ArgParser
{
protected:
    // Arguments are stored in a dictionary
    std::map<std::string, std::string> args;

    // Potential values are stored in a dictionary of sets
    std::map<std::string, std::set<std::string>> validArgs;

public:
    void addArgument(const std::string &name, const std::string &defaultValue, std::set<std::string> validValues = {});
    // void addArgument(const std::string &name, const std::string &defaultValue);
    void parse(int argc, char *argv[]);
    std::string get(const std::string &name);
};
#endif