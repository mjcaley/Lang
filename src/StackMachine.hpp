#pragma once
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>
#include <boost/spirit/home/x3.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


const bool debug { true };

namespace Lang
{
    enum InstructionSet
    {
        HALT    = 0x00000000,
        
        PUSH    = 0x00000001,
        POP     = 0x00000002,
        
        ADD     = 0x00000003,
        SUB     = 0x00000004,
        MUL     = 0x00000005,
        DIV     = 0x00000006,
        MOD     = 0x00000007,
        
        JMP     = 0x00000008,
        
        LOAD    = 0x00000009,
        STORE   = 0x0000000A,
        
        PRNT    = 0x0000000B
    };
    
    class StackMachine
    {
    public:
        StackMachine(int32_t memory_size = 1000000)
        {
            memory.reserve(memory_size);
        };
        
        void loadProgram(std::vector<int32_t> p) { program = p; };
        void loadProgram(std::string& p) {  };
        
        void run();
        
    private:
        unsigned ip { 0 };  // Instruction pointer
        unsigned fp;        // Frame pointer
        bool running { false };

        std::vector<int32_t> program { 0 };
        std::stack<int32_t> stack;
        std::vector<int32_t> memory;
        
        // Arithmetic
        void add();
        void subtract();
        void multiply();
        void divide();
        void modulus();
        
        // Control flow
        void jump();
        
        void load();
        void store();
        
        void print();
    };
    
    
    
    
    
    namespace sm_ast
    {
        struct operand
        {
            int32_t value;
        };
        
        struct instruction
        {
            int32_t value;
        };
        
        struct program
        {
            std::vector<int32_t> values;
        };
    }
    
    struct eval
    {
        void operator=(int32_t i)
        {
            std::cout << "equals" << i << std::endl;
        }
        
        int operator()(const int32_t i)
        {
            std::cout << "int op " << i << std::endl;
            code.push_back(i);
            return 0;
        }
        
        int operator()(const std::string s)
        {
            std::cout << "string op " << s << std::endl;
            if (s == "HALT") { code.push_back(HALT); return 0; }
            
            else if (s == "PUSH") { code.push_back(PUSH); return 0; }
            else if (s == "POP")  { code.push_back(POP); return 0; }
            
            else if (s == "ADD")  { code.push_back(ADD); return 0; }
            else if (s == "SUB")  { code.push_back(SUB); return 0; }
            else if (s == "MUL")  { code.push_back(MUL); return 0; }
            else if (s == "DIV")  { code.push_back(DIV); return 0; }
            else if (s == "MOD")  { code.push_back(MOD); return 0; }
            
            else if (s == "JMP")  { code.push_back(JMP); return 0; }
            
            else if (s == "LOAD")  { code.push_back(LOAD); return 0; }
            else if (s == "STORE") { code.push_back(STORE); return 0; }
            
            else if (s == "PRNT")  { code.push_back(PRNT); return 0; }
            
            else {
                // Invalid instruction
                return -1;
            }
        }
        
    private:
        std::vector<int32_t> code;
    };
    
    
    namespace sm_grammar
    {
        namespace x3 = boost::spirit::x3;
        
        using x3::int_;
        using x3::string;
        using x3::_attr;
        using x3::_val;
        using x3::symbols;
        
        const symbols<int32_t> nullary_sym
        {
            { "HALT", HALT },
            { "POP", POP },
            { "ADD", ADD },
            { "SUB", SUB },
            { "MUL", MUL },
            { "DIV", DIV },
            { "MOD", MOD },
            { "PRNT", PRNT }
        };
        
        const symbols<int32_t> unary_sym
        {
            { "PUSH", PUSH },
            { "JMP", JMP },
            { "LOAD", LOAD },
            { "STORE", STORE }
        };
        
        
        x3::rule<class operand, int32_t> const operand("operand");
        x3::rule<class nullary_op, int32_t> const nullary_op("nullary_op");
        x3::rule<class unary_op, int32_t> const unary_op("unary_op");
        x3::rule<class program, std::vector<int32_t>> const program("program");
        //x3::rule<class instruction, int32_t> const instruction("instruction");
        //x3::rule<class program, sm_ast::program> const program("program");
        
        auto const operand_def = int_;
        auto const nullary_op_def = nullary_sym;
        auto const unary_op_def = unary_sym >> operand;
        auto const program_def = ( nullary_op | unary_op ) >> *( nullary_op | unary_op );
        
        
        auto const instruction_def = *(
            string("HALT")                 |
            string("PUSH")     >> operand  |
            string("POP")                  |
            string("ADD")                  |
            string("SUB")                  |
            string("MUL")                  |
            string("DIV")                  |
            string("MOD")                  |
            string("JMP")      >> operand  |
            string("LOAD")     >> operand  |
            string("STORE")    >> operand  |
            string("PRNT"));
        
//        auto const program_def = *instruction;
        
        //BOOST_SPIRIT_DEFINE(operand/*, instruction/*, program*/);
        BOOST_SPIRIT_DEFINE(operand, nullary_op, unary_op, program);
    };
}

BOOST_FUSION_ADAPT_STRUCT(Lang::sm_ast::operand, (int32_t, value))
BOOST_FUSION_ADAPT_STRUCT(Lang::sm_ast::instruction, (int32_t, value))