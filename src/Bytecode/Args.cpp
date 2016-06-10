#include "Args.hpp"
#include <boost/algorithm/string/predicate.hpp>


bool parseArgs(int argc, char* argv[], Args& parsed_args)
{
    using namespace boost::algorithm;
    
    if (argc > 3 || argc <= 1)
    {
        // Wrong number of arguments
        std::cout << "Error: Incorrect number of  arguments\n";
        return false;
    }
    
    for (int i = 1; i < argc; i++)
    {
        if (equals(argv[i], "--help"))
        {
            parsed_args.help = true;
        }
        else
        {
            parsed_args.filenames.emplace_back(argv[i]);
        }
    }
    
    return true;
}