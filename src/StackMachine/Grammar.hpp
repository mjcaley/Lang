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
        { "PRNT", PRNT },   { "prnt", PRNT },
        { "RET", RET },     { "ret", RET }
    };
    
    const symbols<int32_t> unary_sym
    {
        { "PUSH", PUSH },   { "push", PUSH },
        { "LOAD", LOAD },   { "load", LOAD },
        { "STORE", STORE }, { "store", STORE }
    };
    
    const symbols<int32_t> binary_sym
    {
    };
    
    const symbols<int32_t> jump_sym
    {
        { "JMP", JMP },     { "jmp", JMP },
        { "JT", JT },       { "jt", JT },
        { "JF", JF },       { "jf", JF }
    };
    
    const symbols<int32_t> call_sym
    {
        { "CALL", CALL },     { "call", CALL }
    };
    
    
    x3::rule<class identifier, std::string> const identifier("identifier");
    x3::rule<class operand, AST::Operand> const operand("operand");
    x3::rule<class nullary_op, AST::Nullary> const nullary_op("nullary_op");
    x3::rule<class unary_op, AST::Unary > const unary_op("unary_op");
    x3::rule<class binary_op, AST::Binary > const binary_op("binary_op");
    
    x3::rule<class label, AST::Label > const label("label");
    x3::rule<class jump_op, AST::Jump > const jump_op("jump_op");
    x3::rule<class call_op, AST::Call > const call_op("call_op");
    
    x3::rule<class program, AST::Program > const program("program");
    
    
    auto const identifier_def = lexeme[(alpha > *( alnum | char_('_') ))];
    auto const operand_def = int_;
    auto const nullary_op_def = nullary_sym;
    auto const unary_op_def = unary_sym >> operand;
    auto const binary_op_def = binary_sym >> operand >> operand;
    
    auto const label_def = lexeme[ identifier >> ':' ];
    auto const jump_op_def = jump_sym >> ( identifier | int_ );
    auto const call_op_def = call_sym >> ( identifier | int_ ) >> operand;
    
    auto const program_def = *( (nullary_op | unary_op | binary_op | label | jump_op | call_op) );
    
    BOOST_SPIRIT_DEFINE(identifier);
    BOOST_SPIRIT_DEFINE(label);
    BOOST_SPIRIT_DEFINE(operand);
    BOOST_SPIRIT_DEFINE(nullary_op);
    BOOST_SPIRIT_DEFINE(unary_op);
    BOOST_SPIRIT_DEFINE(binary_op);
    BOOST_SPIRIT_DEFINE(jump_op);
    BOOST_SPIRIT_DEFINE(call_op);
    BOOST_SPIRIT_DEFINE(program);
    
} };