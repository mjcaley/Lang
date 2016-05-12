#pragma once
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/algorithm/string/predicate.hpp>


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
    
    struct Label
    {
        std::string name;
    };
    
    struct Jump
    {
        Instruction instruction;
        std::string label;
    };
    
    struct InstructionCode : x3::variant< Unary, Nullary, Label, Jump >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<InstructionCode>;

} }


namespace StackMachine { namespace AST {
    
    struct CodeGenerator : public boost::static_visitor<>
    {
        std::vector<int32_t> byte_code;
        
        void operator()(AST::Label& label)
        {
            label_map[label.name] = byte_code.size();
        }
        
        void operator()(AST::Jump& jump)
        {
            byte_code.emplace_back(jump.instruction.byte_code);
            byte_code.emplace_back(label_map[jump.label]);
        }
        
        void operator()(AST::Unary& unary_op)
        {
            byte_code.emplace_back(unary_op.instruction.byte_code);
            byte_code.emplace_back(unary_op.operand.byte_code);
        }
        
        void operator()(AST::Nullary& nullary_op)
        {
            byte_code.emplace_back(nullary_op.instruction.byte_code);
        }
        
    private:
        std::map<std::string, int32_t> label_map;
    };
    
    std::vector<int32_t> generate_byte_code(AST::Program& instructions)
    {
        CodeGenerator generator;
        for (auto& ast : instructions)
        {
            boost::apply_visitor(generator, ast);
        }
        
        return generator.byte_code;
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

BOOST_FUSION_ADAPT_STRUCT(StackMachine::AST::Label, (std::string, name));

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Jump,
                          (StackMachine::AST::Instruction, instruction),
                          (std::string, label)
                          );