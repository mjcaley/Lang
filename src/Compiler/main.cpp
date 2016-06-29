#include <fstream>
#include <iostream>
#include <boost/program_options.hpp>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include "Language/Language.hpp"
#include "Bytecode/Bytecode.hpp"


const std::string EXEC_NAME = "langc";
const int VERSION_MAJOR = 0;
const int VERSION_MINOR = 1;


bool compile(const std::string& src, const std::string& dest)
{
    namespace x3 = boost::spirit::x3;
    using boost::spirit::make_default_multi_pass;
    using namespace Lang;
    
    std::basic_ifstream<char32_t> in(src);
    in.unsetf(std::ios::skipws);
    
    if (!in.is_open())
    {
        return false;
    }
    
    using stream_iterator = std::istreambuf_iterator<char32_t>;
    auto iter = make_default_multi_pass(stream_iterator(in));
    auto end = make_default_multi_pass(stream_iterator());
    
    Lang::Language::AST::Program ast;
    auto& grammar = Lang::Language::Grammar::program;
    bool success = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    auto smf = Lang::Language::compile(ast);
    smf->write(dest);
    
    return success;
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    
    using std::cout;
    using std::endl;
    using std::string;
    
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "Display this help message")
        ("source", po::value<std::string>(), "source file")
        ("destination", po::value<std::string>(), "destination file")
    ;
    
    
    po::variables_map var_map;
    po::store(po::parse_command_line(argc, argv, desc), var_map);
    po::notify(var_map);
    
    if (var_map.count("help"))
    {
        cout << desc << endl;
    }
    else if (var_map.count("source") && var_map.count("destination"))
    {
        bool success = compile(var_map["source"].as<string>(),
                               var_map["destination"].as<string>());
    }
    else
    {
        cout << EXEC_NAME << '\n' << desc << endl;
    }
    
    return 0;
}