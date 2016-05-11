#pragma once
#include "AST.hpp"


namespace StackMachine { namespace Grammar {
    
    namespace x3 = boost::spirit::x3;
    namespace AST = StackMachine::AST;
    
    using x3::int_;
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
    
    
    x3::rule<class operand, AST::Operand> const operand("operand");
    x3::rule<class nullary_op, AST::Nullary> const nullary_op("nullary_op");
    x3::rule<class unary_op, AST::Unary > const unary_op("unary_op");
    x3::rule<class program, AST::Program > const program("program");
    
    auto const operand_def = int_;
    auto const nullary_op_def = nullary_sym;
    auto const unary_op_def = unary_sym >> operand;
    auto const program_def = *( (nullary_op | unary_op ) >> ';' );
    
    BOOST_SPIRIT_DEFINE(operand, nullary_op, unary_op, program);
    
} };