#pragma once
#include "Bytecode/AST.hpp"
#include "VM/VM.hpp"


using i32 = int32_t;

namespace Lang { namespace Bytecode { namespace Grammar {
    
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    using namespace Lang::VM;
    
    using x3::alpha;
    using x3::alnum;
    using x3::char_;
    using x3::eol;
    using x3::int_;
    using x3::lexeme;
    using x3::space;
    using x3::symbols;
    
    auto const skipper = space | lexeme[ ';' >> *(char_ - eol) >> eol ];
    
    const symbols<i32> nullary_sym
    {
        { "HALT", HALT },   { "halt", HALT },
        { "POP", POP },     { "pop", POP },
        { "ADD", ADD },     { "add", ADD },
        { "SUB", SUB },     { "sub", SUB },
        { "MUL", MUL },     { "mul", MUL },
        { "DIV", DIV },     { "div", DIV },
        { "MOD", MOD },     { "mod", MOD },
        { "EQ", EQ },       { "eq", EQ },
        { "LT", LT },       { "lt", LT },
        { "GT", GT },       { "gt", GT },
        { "PRNT", PRNT },   { "prnt", PRNT },
        { "RET", RET },     { "ret", RET },
        { "DUP", DUP },     { "dup", DUP }
    };
    
    const symbols<i32> unary_sym
    {
        { "PUSH", PUSH },   { "push", PUSH },
        { "LOAD", LOAD },   { "load", LOAD },
        { "STORE", STORE }, { "store", STORE }
    };
    
    const symbols<i32> jump_sym
    {
        { "JMP", JMP },     { "jmp", JMP },
        { "JT", JT },       { "jt", JT },
        { "JF", JF },       { "jf", JF }
    };
    
    const symbols<i32> call_sym
    {
        { "CALL", CALL },     { "call", CALL }
    };
    
    
    x3::rule<class identifier, std::string> const identifier("identifier");
    x3::rule<class operand, AST::Operand> const operand("operand");
    x3::rule<class nullary_op, AST::Nullary> const nullary_op("nullary_op");
    x3::rule<class unary_op, AST::Unary > const unary_op("unary_op");
    
    x3::rule<class label, AST::Label > const label("label");
    x3::rule<class jump_op, AST::Jump > const jump_op("jump_op");
    x3::rule<class call_op, AST::Call > const call_op("call_op");
    
    x3::rule<class program, AST::Program > const program("program");
    
    
    auto const identifier_def = lexeme[(alpha >> *( alnum | char_('_') ))];
    auto const operand_def = int_;
    auto const nullary_op_def = nullary_sym;
    auto const unary_op_def = unary_sym >> operand;
    
    auto const label_def = lexeme[ identifier >> ':' ];
    auto const jump_op_def = jump_sym >> ( identifier | int_ );
    auto const call_op_def = call_sym >> ( identifier | int_ );
    
    auto const program_def = *( (label | nullary_op | unary_op | jump_op | call_op) );
    
    BOOST_SPIRIT_DEFINE(identifier);
    BOOST_SPIRIT_DEFINE(label);
    BOOST_SPIRIT_DEFINE(operand);
    BOOST_SPIRIT_DEFINE(nullary_op);
    BOOST_SPIRIT_DEFINE(unary_op);
    BOOST_SPIRIT_DEFINE(jump_op);
    BOOST_SPIRIT_DEFINE(call_op);
    BOOST_SPIRIT_DEFINE(program);
    
} } };