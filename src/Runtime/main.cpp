#include "StackMachineFile.hpp"
#include "VM/VM.hpp"
#include <boost/program_options.hpp>


int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    namespace po = boost::program_options;
    using namespace Lang;
    
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Display this help message")
    ("source", po::value<std::string>(), "source file")
    ;
    
    po::variables_map var_map;
    po::store(po::parse_command_line(argc, argv, desc), var_map);
    po::notify(var_map);
    
    if (var_map.count("help"))
    {
        cout << desc << endl;
    }
    else if (auto src = var_map.count("source"))
    {
        auto file = LangFile::create(src);
        
        auto vm = VM();
        vm.loadProgram(file);
        vm.run();
    }
    
    return 0;
}