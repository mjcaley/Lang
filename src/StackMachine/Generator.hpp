#include "AST.hpp"


namespace StackMachine { namespace AST {
    
    struct LabelPreprocessor : public boost::static_visitor<>
    {
        LabelPreprocessor(std::map<std::string, int32_t>& label_map)
        : label_map(label_map) {}
        
        void operator()(Label& label)
        {
            label_map[label.name] = address;
        }
        
        void operator()(Jump& jump)
        {
            address += 2;
        }
        
        void operator()(Unary& unary_op)
        {
            address += 2;
        }
        
        void operator()(Nullary& nullary_op)
        {
            address++;
        }
        
        void operator()(Binary& binary_op)
        {
            address += 3;
        }
        
        void operator()(Call& call_op)
        {
            address += 3;
        }
        
    private:
        int address { 0 };
        std::map<std::string, int32_t>& label_map;
    };
    
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
        CodeGenerator(std::vector<int32_t>& byte_code, std::map<std::string, int32_t>& label_map)
        : byte_code(byte_code), label_map(label_map) {}
        
        void operator()(Label& label) {}
        
        void operator()(Jump& jump)
        {
            byte_code.emplace_back(jump.instruction);
            JumpArgGen arg_generator(byte_code, label_map);
            boost::apply_visitor(arg_generator, jump.position);
        }
        
        void operator()(Call& call)
        {
            byte_code.emplace_back(call.instruction);
            JumpArgGen arg_generator(byte_code, label_map);
            boost::apply_visitor(arg_generator, call.position);
            byte_code.emplace_back(call.operand);
        }
        
        void operator()(Unary& unary_op)
        {
            byte_code.emplace_back(unary_op.instruction);
            byte_code.emplace_back(unary_op.operand);
        }
        
        void operator()(Nullary& nullary_op)
        {
            byte_code.emplace_back(nullary_op.instruction);
        }
        
        void operator()(Binary& binary_op)
        {
            byte_code.emplace_back(binary_op.instruction);
            byte_code.emplace_back(binary_op.operand1);
            byte_code.emplace_back(binary_op.operand2);
        }
        
    private:
        std::vector<int32_t>& byte_code;
        std::map<std::string, int32_t>& label_map;
    };
    
    std::vector<int32_t> generate_byte_code(Program& instructions)
    {
        std::map<std::string, int32_t> label_map;
        std::vector<int32_t> byte_code;
        
        LabelPreprocessor label_preprocessor(label_map);
        for (auto& ast : instructions)
        {
            boost::apply_visitor(label_preprocessor, ast);
        }
        
        CodeGenerator generator(byte_code, label_map);
        for (auto& ast : instructions)
        {
            boost::apply_visitor(generator, ast);
        }
        
        return byte_code;
    }
    
} }