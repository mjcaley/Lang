#pragma once
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace StackMachine { namespace AST {

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
    
    struct InstructionCode : x3::variant< Binary, Unary, Nullary, Label, Jump >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<InstructionCode>;

} }


BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Nullary,
                          (StackMachine::AST::Instruction, instruction)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Unary,
                          (StackMachine::AST::Instruction, instruction),
                          (StackMachine::AST::Operand, operand)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Binary,
                          (StackMachine::AST::Instruction, instruction),
                          (StackMachine::AST::Operand, operand1),
                          (StackMachine::AST::Operand, operand2)
                          );

BOOST_FUSION_ADAPT_STRUCT(StackMachine::AST::Label, (std::string, name));

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Jump,
                          (StackMachine::AST::Instruction, instruction),
                          (StackMachine::AST::JumpArg, position)
                          );