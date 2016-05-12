#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include "Args.hpp"
#include "StackMachine.hpp"


const std::string NAME = "StackMachine";
const int VERSION_MAJOR = 1;
const int VERSION_MINOR = 0;
const int VERSION_PATCH = 0;

const std::vector<int32_t> MAGIC { 0x48, 0x52, 0x42, 0x44, 0x52, 0x47, 0x4E, 0x53 };


void printUsage()
{
    std::cout << NAME <<
    " v" << VERSION_MAJOR <<
    '.' << VERSION_MINOR <<
    '.' << VERSION_PATCH << '\n';
    std::cout << "Running usage:\n"
    << '\t' << NAME << " COMPILED_FILE\n"
    << "Compiler usage:\n"
    << '\t' << NAME << " SOURCE_FILE DEST_FILE" << std::endl;
}

bool verifyFile(std::vector<int32_t>& program)
{
    for (int i = 0; i < MAGIC.size(); i++)
    {
        if (MAGIC[i] != program[i])
        {
            return false;
        }
    }
    
    return true;
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

bool runProgram(std::string& filename)
{
    using namespace StackMachine;
    
    std::ifstream in(filename, std::ios::binary);
    std::vector<int32_t> program;
    if (in.is_open())
    {
        std::vector<int32_t> byte_code(
            (std::istreambuf_iterator<char>(in)),
            (std::istreambuf_iterator<char>())
        );
        if (!verifyFile(byte_code))
        {
            std::cout << "Error: Could not verify file" << std::endl;
            return false;
        }
        program.insert(program.end(), byte_code.begin()+8, byte_code.end());
    }
    
    auto vm = VM();
    vm.loadProgram(program);
    bool status = vm.run();
    
    return status;
}

bool compileProgram(std::string& input_filename, std::string& output_filename)
{
    std::pair<bool, std::vector<int32_t>> compiled;
    
    {
        std::ifstream in(input_filename);
        in.unsetf(std::ios::skipws);
        
        std::string src;
        if (in.is_open())
        {
            std::ostringstream contents;
            contents << in.rdbuf();
            src = contents.str();
        }
        
        compiled = compile(src);
    }
    
    {
        std::ofstream out(output_filename, std::ios::binary);
        if (out.is_open() && compiled.first)
        {
            for (auto& m : MAGIC)
            {
                out.put(m);
            }
            for (auto& i : compiled.second)
            {
                out.put(i);
            }
        }
    }
    
    return compiled.first;
}

int main(int argc, char* argv[])
{
    Args args;
    bool status = parseArgs(argc, argv, args);
    
    if (!status || args.help || args.filenames.size() <= 0)
    {
        printUsage();
        return 0;
    }
    else if (args.filenames.size() == 1)
    {
        bool status = runProgram(args.filenames[0]);
        return status;
    }
    else if (args.filenames.size() == 2)
    {
        bool status = compileProgram(args.filenames[0], args.filenames[1]);
        return status;
    }
    
    std::cout << "Unknown error\n\n";
    printUsage();
    
    return 1;
}