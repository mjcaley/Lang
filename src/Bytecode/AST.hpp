#pragma once
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace Lang { namespace Bytecode { namespace AST {

    namespace x3 = boost::spirit::x3;
    
    using Operand = int32_t;
    using Instruction = int32_t;
    
    struct Nullary
    {
        Instruction instruction;
    };
    
    struct Unary
    {
        Instruction instruction;
        Operand operand;
    };
    
    struct Binary
    {
        Instruction instruction;
        Operand operand1;
        Operand operand2;
    };
    
    struct Label
    {
        std::string name;
    };
    
    struct JumpArg : x3::variant< int32_t, std::string >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct Jump
    {
        Instruction instruction;
        JumpArg position;
    };
    
    struct Call
    {
        Instruction instruction;
        JumpArg position;
        Operand operand;
    };
    
    struct InstructionCode : x3::variant< Binary, Unary, Nullary, Label, Jump, Call >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<InstructionCode>;

} } }


BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Bytecode::AST::Nullary,
                          (Lang::Bytecode::AST::Instruction, instruction)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Bytecode::AST::Unary,
                          (Lang::Bytecode::AST::Instruction, instruction),
                          (Lang::Bytecode::AST::Operand, operand)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Bytecode::AST::Binary,
                          (Lang::Bytecode::AST::Instruction, instruction),
                          (Lang::Bytecode::AST::Operand, operand1),
                          (Lang::Bytecode::AST::Operand, operand2)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Bytecode::AST::Call,
                          (Lang::Bytecode::AST::Instruction, instruction),
                          (Lang::Bytecode::AST::JumpArg, position),
                          (Lang::Bytecode::AST::Operand, operand)
                          );

BOOST_FUSION_ADAPT_STRUCT(Lang::Bytecode::AST::Label, (std::string, name));

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Bytecode::AST::Jump,
                          (Lang::Bytecode::AST::Instruction, instruction),
                          (Lang::Bytecode::AST::JumpArg, position)
                          );