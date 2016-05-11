#include "StackMachine.hpp"
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <boost/algorithm/string/predicate.hpp>


struct Args
{
    std::vector<std::string> filenames;
    bool help;
};

Args parse_args(int argc, char* argv[])
{
    using namespace boost::algorithm;
    
    if (argc > 3 || argc <= 1)
    {
        // Wrong number of arguments
        std::cout << "Error: Incorrect number of  arguments\n";
        std::cout << "Usage: StackMachine SRC DEST" << std::endl;
        std::exit(-1);
    }
    
    Args args;
    
    for (int i = 1; i < argc; i++)
    {
        if (equals(argv[i], "--help"))
        {
            args.help = true;
        }
        else
        {
            args.filenames.emplace_back(argv[i]);
        }
    }
    
    return args;
}

std::pair<bool, std::vector<int32_t>> compile(std::string& program)
{
    using namespace StackMachine;
    namespace x3 = boost::spirit::x3;
    
    auto iter = program.begin();
    auto end = program.end();
    AST::Program ast;
    auto& grammar = Grammar::program;
    
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    if (result)
    {
        return std::make_pair(result, AST::generate_byte_code(ast) );
    }
    else
    {
        return std::make_pair(result, std::vector<int32_t>() );
    }
}

int main(int argc, char* argv[])
{
    using namespace StackMachine;
    namespace x3 = boost::spirit::x3;
    
    Args args = parse_args(argc, argv);
    if (args.filenames.size() == 1)
    {
        std::cout << "Binary file, running" << std::endl;
        
        std::ifstream in(args.filenames[0], std::ios::binary);
        std::vector<int32_t> program;
        if (in.is_open())
        {
            std::vector<char> buffer (
                                      (std::istreambuf_iterator<char>(in)),
                                      (std::istreambuf_iterator<char>())
                                      );
            program.insert( program.end(), buffer.begin(), buffer.end() );
        }
        
        auto vm = VM();
        vm.loadProgram(program);
        vm.run();
        
        return 0;
    }
    else if (args.filenames.size() == 2)
    {
        std::cout << "Text file, compiling" << std::endl;
        
        std::pair<bool, std::vector<int32_t>> dest;
        
        {
            std::ifstream in(args.filenames[0]);
            in.unsetf(std::ios::skipws);
            
            std::string src;
            if (in.is_open())
            {
                std::ostringstream contents;
                contents << in.rdbuf();
                src = contents.str();
            }
            
            dest = compile(src);
        }
        
        std::ofstream out(args.filenames[1], std::ios::binary);
        if (out.is_open() && dest.first)
        {
            for (auto& i : dest.second)
            {
                out.put(i);
            }
        }
        
        return 0;
    }
    else
    {
        // display help
        return 0;
    }
}