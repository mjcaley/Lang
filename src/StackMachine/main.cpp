#ifndef DEBUG_BUILD
#define DEBUG_BUILD true
#endif

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

std::pair<bool, std::unique_ptr<StackMachine::StackMachineFile>> compile(std::string& program)
{
    using namespace StackMachine;
    namespace x3 = boost::spirit::x3;
    
    auto iter = program.begin();
    auto end = program.end();
    AST::Program ast;
    auto& grammar = Grammar::program;
    
    bool result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    
    auto smf = std::make_unique<StackMachineFile>();
    if (result && iter == end)
    {
        compile(ast, smf.get());
        return std::make_pair(result, std::move(smf));
    }
    else
    {
        std::cout << "Error: could not parse source" << std::endl;
        return std::make_pair(false, std::move(smf));
    }
}

bool runProgram(std::string& filename)
{
    using namespace StackMachine;
    
    auto program = StackMachineFile::create(filename);
    
    auto vm = VM();
#ifdef DEBUG_BUILD
    vm.debug = true;
#endif
    vm.loadProgram(std::move(program));
    bool status = vm.run();
    
    return status;
}

bool compileProgram(std::string& input_filename, std::string& output_filename)
{
    std::pair<bool, std::unique_ptr<StackMachine::StackMachineFile>> compiled;
    
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
    
    compiled.second->write(output_filename);
    
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
        if (status) { return 0; }
        else { return 1; }
    }
    else if (args.filenames.size() == 2)
    {
        bool status = compileProgram(args.filenames[0], args.filenames[1]);
        if (status) { return 0; }
        else { return 1; }
    }
    
    std::cout << "Unknown error\n\n";
    printUsage();
    
    return 1;
}