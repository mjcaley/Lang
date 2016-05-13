#include "AST.hpp"


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
        
        void operator()(Label& label)
        {
            label_map[label.name] = byte_code.size();
        }
        
        void operator()(Jump& jump)
        {
            byte_code.emplace_back(jump.instruction.byte_code);
            JumpArgGen arg_generator(byte_code, label_map);
            boost::apply_visitor(arg_generator, jump.position);
        }
        
        void operator()(Unary& unary_op)
        {
            byte_code.emplace_back(unary_op.instruction.byte_code);
            byte_code.emplace_back(unary_op.operand.byte_code);
        }
        
        void operator()(Nullary& nullary_op)
        {
            byte_code.emplace_back(nullary_op.instruction.byte_code);
        }
        
    private:
        std::vector<int32_t>& byte_code;
        std::map<std::string, int32_t> label_map;
    };
    
    std::vector<int32_t> generate_byte_code(Program& instructions)
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