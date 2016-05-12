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
    
    struct Label
    {
        std::string name;
    };
    
    struct JumpArg : x3::variant< int32_t, std::string>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct Jump
    {
        Instruction instruction;
        JumpArg position;
    };
    
    struct InstructionCode : x3::variant< Unary, Nullary, Label, Jump >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<InstructionCode>;

} }


namespace StackMachine { namespace AST {
    
    struct JumpArgGen : public boost::static_visitor<>
    {
        JumpArgGen(std::vector<int32_t>& byte_code,
                std::map<std::string, int32_t>& label_map)
        : byte_code(byte_code), label_map(label_map) {};
        
        void operator()(int32_t& position)
        {
            byte_code.emplace_back(position);
        }
        
        void operator()(std::string& position)
        {
            byte_code.emplace_back(label_map[position]);
        }
        
    private:
        std::vector<int32_t>& byte_code;
        std::map<std::string, int32_t>& label_map;
    };
    
    struct CodeGenerator : public boost::static_visitor<>
    {
        CodeGenerator(std::vector<int32_t>& byte_code)
        : byte_code(byte_code) {}
        
        void operator()(AST::Label& label)
        {
            label_map[label.name] = byte_code.size();
        }
        
        void operator()(AST::Jump& jump)
        {
            byte_code.emplace_back(jump.instruction.byte_code);
            JumpArgGen arg_generator(byte_code, label_map);
            boost::apply_visitor(arg_generator, jump.position);
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
        std::vector<int32_t>& byte_code;
        std::map<std::string, int32_t> label_map;
    };
    
    std::vector<int32_t> generate_byte_code(AST::Program& instructions)
    {
        std::vector<int32_t> byte_code;
        
        CodeGenerator generator(byte_code);
        for (auto& ast : instructions)
        {
            boost::apply_visitor(generator, ast);
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

BOOST_FUSION_ADAPT_STRUCT(StackMachine::AST::Label, (std::string, name));

BOOST_FUSION_ADAPT_STRUCT(
                          StackMachine::AST::Jump,
                          (StackMachine::AST::Instruction, instruction),
                          (StackMachine::AST::JumpArg, position)
                          );