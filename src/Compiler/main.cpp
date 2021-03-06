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


template<typename T>
std::basic_ifstream<T> make_istream(const std::string& filename)
{
    std::basic_ifstream<T> stream(filename);
    stream.unsetf(std::ios::skipws);
    
    return stream;
}

template<typename T>
std::pair< boost::spirit::multi_pass<std::istreambuf_iterator<T>>,
           boost::spirit::multi_pass<std::istreambuf_iterator<T>> >
make_spirit_stream(std::basic_ifstream<T>& file)
{
    using boost::spirit::make_default_multi_pass;
    
    auto iter_pair = std::make_pair(
        make_default_multi_pass(std::istreambuf_iterator<T>(file)),
        make_default_multi_pass(std::istreambuf_iterator<T>())
    );
    
    return iter_pair;
}

bool compile(const std::string& src, const std::string& dest, bool print_ast = false)
{
    namespace x3 = boost::spirit::x3;
    using namespace Lang;
    
    auto in = make_istream<char>(src);
    if (!in.is_open())
    {
        return false;
    }
    auto iter = make_spirit_stream<char>(in);
    
    Lang::Language::AST::Program ast;
    auto& grammar = Lang::Language::Grammar::program;
    bool success = x3::phrase_parse(iter.first, iter.second, grammar, x3::space, ast);
    auto smf = Lang::Language::compile(ast, print_ast);
    smf->write(dest);
    
    return success;
}

int main(int argc, char* argv[])
{
    namespace po = boost::program_options;
    
    using std::cout;
    using std::endl;
    using std::string;
    
    po::options_description desc("Program options");
    desc.add_options()
        ("help,h", "Display this help message")
        ("source", po::value<std::string>(), "source file")
        ("destination", po::value<std::string>()->default_value("a.lang"), "destination file")
    ;
    po::positional_options_description pos_desc;
    pos_desc.add("source", -1);
    
    po::options_description debug_desc("Debug options");
    debug_desc.add_options()
        ("print-ast", po::bool_switch()->default_value(false), "Print out the AST after each stage")
    ;
    
    po::variables_map var_map;
    po::store(po::command_line_parser(argc, argv).
              options(desc).
              positional(pos_desc).
              allow_unregistered().
              run(),
              var_map);
    po::store(po::command_line_parser(argc, argv).
              options(debug_desc).
              allow_unregistered().
              run(),
              var_map);
    po::notify(var_map);
    
    if (var_map.count("help"))
    {
        cout << desc << endl;
    }
    else if (var_map.count("source"))
    {
        bool success = compile(var_map["source"].as<string>(),
                               var_map["destination"].as<string>(),
                               var_map["print-ast"].as<bool>());
    }
    else
    {
        cout << EXEC_NAME << '\n' << desc << '\n' << debug_desc << endl;
    }
    
    return 0;
}
