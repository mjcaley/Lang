#pragma once
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace StackMachine { namespace AST {

    namespace x3 = boost::spirit::x3;
    
    struct Operand { int32_t byte_code; };
    struct Instruction { int32_t byte_code; };
    
    
    struct Nullary
    {
        Instruction instruction;
    };
    
    struct Unary
    {
        Instruction instruction;
        Operand operand;
    };
    
    struct InstructionCode : x3::variant< Unary, Nullary >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<InstructionCode>;

} }


namespace StackMachine { namespace AST {
    
    struct Translator : public boost::static_visitor<std::vector<int32_t>>
    {
        std::vector<int32_t> operator()(AST::Unary& unary_op) const
        {
            return {
                unary_op.instruction.byte_code,
                unary_op.operand.byte_code
            };
        }
        
        std::vector<int32_t> operator()(AST::Nullary& nullary_op) const
        {
            return { nullary_op.instruction.byte_code };
        }
    };
    
    std::vector<int32_t> generate_byte_code(AST::Program& instructions)
    {
        std::vector<int32_t> byte_code;
        for (auto& instruction : instructions)
        {
            auto code = boost::apply_visitor(Translator(), instruction);
            byte_code.insert( byte_code.end(), code.begin(), code.end());
        }
        
        return byte_code;
    }

} }


BOOST_FUSION_ADAPT_STRUCT(StackMachine::AST::Operand, (int32_t, byte_code));

BOOST_FUSION_ADAPT_STRUCT(StackMachine::AST::Instruction, (int32_t, byte_code));

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Nullary,
                          (StackMachine::AST::Instruction, instruction)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Unary,
                          (StackMachine::AST::Instruction, instruction),
                          (StackMachine::AST::Operand, operand)
                          );