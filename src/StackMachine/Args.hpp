#pragma once
#include <iostream>
#include <vector>


struct Args
{
    std::vector<std::string> filenames;
    bool help;
};

bool parseArgs(int argc, char* argv[], Args& parsed_args);