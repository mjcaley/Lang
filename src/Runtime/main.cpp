#include "LangFile.hpp"
#include "VM/VM.hpp"
#include <boost/program_options.hpp>


int main(int argc, char* argv[])
{
    using std::cout;
    using std::endl;
    using std::string;
    namespace po = boost::program_options;
    using namespace Lang;
    
    po::options_description desc("Allowed options");
    desc.add_options()
    ("help,h", "Display this help message")
    ("source", po::value<std::string>(), "source file")
    ;
    
    po::positional_options_description p;
    p.add("source", 1);
    
    po::variables_map var_map;
    po::store(po::command_line_parser(argc, argv).
              options(desc).positional(p).run(), var_map);
    po::notify(var_map);
    
    if (var_map.count("help"))
    {
        cout << desc << endl;
    }
    else if (var_map.count("source"))
    {
        auto file = LangFile::create(var_map["source"].as<string>());
        
        auto vm = VM::VM();
        vm.debug = true;
        vm.loadProgram(std::move(file));
        vm.run();
    }
    else
    {
        cout << desc << endl;
    }
    
    return 0;
}