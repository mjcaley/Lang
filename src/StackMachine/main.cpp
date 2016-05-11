#include "StackMachine.hpp"
#include <iostream>


int main()
{
    using namespace StackMachine;
    namespace x3 = boost::spirit::x3;
    
    auto vm = VM();
    
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
    
    auto iter = program.begin();
    auto end = program.end();
    AST::Program ast;
    auto& grammar = Grammar::program;
    
    bool r = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    if (r)
    {
        std::cout << "Compile successful" << std::endl;
        auto code = AST::generate_byte_code(ast);
        vm.loadProgram(code);
        vm.run();
    }
    else
    {
        std::cout << "Compile failed" << std::endl;
    }
    
    return 0;
}