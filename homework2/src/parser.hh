#ifndef PARSER_HH
#define PARSER_HH
#include <map>
#include <string>

class ArgParser
{
protected:
    // Arguments are stored in a map
    std::map<std::string, std::string> args;

public:
    void addArgument(const std::string &name, const std::string &defaultValue);
    void parse(int argc, char *argv[]);
    std::string get(const std::string &name);
};
#endif