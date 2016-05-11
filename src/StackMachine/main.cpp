#include "StackMachine.hpp"
#include <cstdlib>
#include <iostream>
#include <utility>


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
    
    std::string program =
    "PUSH 10; PUSH 16; ADD;"
    "PRNT;"
    "PUSH 60; PUSH 18; SUB;"
    "PRNT;"
    "PUSH 4; PUSH 3; MUL;"
    "PRNT;"
    "PUSH 12; PUSH 3; DIV;"
    "PRNT;"
    "PUSH 11; PUSH 2; MOD;"
    "PRNT;"
    "PUSH 32; STORE 0;"
    "LOAD 0; PRNT;"
    "HALT;";
    
    auto vm = VM();
    
    {
        auto code = compile(program);
        if (code.first)
        {
            vm.loadProgram(code.second);
        }
        else
        {
            std::cout << "Error: Failed to compile" << std::endl;
            std::exit(-1);
        }
    }
    
    vm.run();

    return 0;
}