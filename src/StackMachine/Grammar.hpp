#pragma once
#include "AST.hpp"


namespace StackMachine { namespace Grammar {
    
    namespace x3 = boost::spirit::x3;
    namespace AST = StackMachine::AST;
    
    using x3::alpha;
    using x3::alnum;
    using x3::char_;
    using x3::int_;
    using x3::lexeme;
    using x3::symbols;
    
    const symbols<int32_t> nullary_sym
    {
        { "HALT", HALT },   { "halt", HALT },
        { "POP", POP },     { "pop", POP },
        { "ADD", ADD },     { "add", ADD },
        { "SUB", SUB },     { "sub", SUB },
        { "MUL", MUL },     { "mul", MUL },
        { "DIV", DIV },     { "div", DIV },
        { "MOD", MOD },     { "mod", MOD },
        { "PRNT", PRNT },   { "prnt", PRNT }
    };
    
    const symbols<int32_t> unary_sym
    {
        { "PUSH", PUSH },   { "push", PUSH },
        { "LOAD", LOAD },   { "load", LOAD },
        { "STORE", STORE }, { "store", STORE }
    };
    
    const symbols<int32_t> jump_sym
    {
        { "JMP", JMP },     { "jmp", JMP }
    };
    
    
    x3::rule<class operand, AST::Operand> const operand("operand");
    x3::rule<class nullary_op, AST::Nullary> const nullary_op("nullary_op");
    x3::rule<class unary_op, AST::Unary > const unary_op("unary_op");
    
    x3::rule<class label, AST::Label > const label("label");
    x3::rule<class jump_op, AST::Jump > const jump_op("jump");
    
    x3::rule<class program, AST::Program > const program("program");
    
    
    auto const operand_def = int_;
    auto const nullary_op_def = nullary_sym;
    auto const unary_op_def = unary_sym >> operand;
    
    auto const label_def = lexeme[ +alnum >> ':' ];
    auto const jump_op_def = jump_sym >> lexeme[+alnum];
    
    auto const program_def = *( (nullary_op | unary_op | label | jump_op) );
    
    BOOST_SPIRIT_DEFINE(label);
    BOOST_SPIRIT_DEFINE(operand);
    BOOST_SPIRIT_DEFINE(nullary_op);
    BOOST_SPIRIT_DEFINE(unary_op);
    BOOST_SPIRIT_DEFINE(jump_op);
    BOOST_SPIRIT_DEFINE(program);
    
} };