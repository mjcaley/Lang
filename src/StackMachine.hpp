#pragma once
#include <cstdint>
#include <iostream>
#include <utility>
#include <stack>
#include <string>
#include <vector>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
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
        namespace x3 = boost::spirit::x3;
        
        struct operand
        {
            int32_t value;
        };
        
        struct instruction
        {
            int32_t value;
        };
        
        struct nullary
        {
            instruction i;
        };
        
        struct unary
        {
            instruction i;
            operand o;
        };
        
        struct instruction_key_value : x3::variant< unary, nullary >
        {
            using base_type::base_type;
            using base_type::operator=;
        };
        
        using program = std::vector<instruction_key_value>;
    }
    
    namespace sm_ast
    {
        namespace x3 = boost::spirit::x3;
        
        struct instruction_visitor : public boost::static_visitor<std::vector<int32_t>>
        {
            std::vector<int32_t> operator()(sm_ast::unary& unary_op) const
            {
                return { unary_op.i.value, unary_op.o.value };
            }
            
            std::vector<int32_t> operator()(sm_ast::nullary& nullary_op) const
            {
                return { nullary_op.i.value };
            }
        };
        
        std::vector<int32_t> encode_variant(sm_ast::program& instructions)
        {
            std::vector<int32_t> finished_code;
            for (auto& i : instructions)
            {
                auto fetch = boost::apply_visitor(sm_ast::instruction_visitor(), i);
                finished_code.insert( finished_code.end(), fetch.begin(), fetch.end());
            }
            
            return finished_code;
        }
    }
    
    namespace sm_grammar
    {
        namespace x3 = boost::spirit::x3;
        
        using x3::int_;
        using x3::symbols;
        
        using x3::_val;
        using x3::_attr;
        
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
        
        
        x3::rule<class operand, sm_ast::operand> const operand("operand");
        x3::rule<class nullary_op, sm_ast::nullary> const nullary_op("nullary_op");
        x3::rule<class unary_op, sm_ast::unary > const unary_op("unary_op");
        x3::rule<class program, sm_ast::program > const program("program");
        
        auto const operand_def = int_;
        auto const nullary_op_def = nullary_sym;
        auto const unary_op_def = unary_sym >> operand;
        auto const program_def = *( (nullary_op | unary_op ) >> ';' );
        
        BOOST_SPIRIT_DEFINE(operand, nullary_op, unary_op, program);
    };
}

BOOST_FUSION_ADAPT_STRUCT(Lang::sm_ast::operand, (int32_t, value));

BOOST_FUSION_ADAPT_STRUCT(Lang::sm_ast::instruction, (int32_t, value));

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::sm_ast::nullary,
                          (Lang::sm_ast::instruction, i)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::sm_ast::unary,
                          (Lang::sm_ast::instruction, i),
                          (Lang::sm_ast::operand, o)
                          );