#pragma once
#include <map>
#include "Bytecode/AST.hpp"


using i32 = int32_t;

namespace Lang { namespace Bytecode { namespace AST {
    
    struct LabelPreprocessor : public boost::static_visitor<>
    {
        LabelPreprocessor(std::map<std::string, i32>& label_map)
        : label_map(label_map) {}
        
        void operator()(const Label& label)
        {
            label_map[label.name] = address;
        }
        
        void operator()(const Jump& jump)
        {
            address += 2;
        }
        
        void operator()(const Unary& unary_op)
        {
            address += 2;
        }
        
        void operator()(const Nullary& nullary_op)
        {
            address++;
        }
        
        void operator()(const Binary& binary_op)
        {
            address += 3;
        }
        
        void operator()(const Call& call_op)
        {
            address += 2;
        }
        
    private:
        int address { 0 };
        std::map<std::string, i32>& label_map;
    };
    
    struct JumpArgGen : public boost::static_visitor<>
    {
        JumpArgGen(std::vector<i32>& byte_code,
                   std::map<std::string, i32>& label_map)
        : byte_code(byte_code), label_map(label_map) {};
        
        void operator()(const i32& position)
        {
            byte_code.emplace_back(position);
        }
        
        void operator()(const std::string& position)
        {
            byte_code.emplace_back(label_map[position]);
        }
        
    private:
        std::vector<i32>& byte_code;
        std::map<std::string, i32>& label_map;
    };
    
    struct CodeGenerator : public boost::static_visitor<>
    {
        CodeGenerator(std::vector<i32>& byte_code, std::map<std::string, i32>& label_map)
        : byte_code(byte_code), label_map(label_map) {}
        
        void operator()(const Label& label) const {}
        void operator()(const Jump& jump) const;
        void operator()(const Call& call) const;
        void operator()(const Unary& unary_op) const;
        void operator()(const Nullary& nullary_op) const;
        void operator()(const Binary& binary_op) const;
        
    private:
        std::vector<i32>& byte_code;
        std::map<std::string, i32>& label_map;
    };
    
} } }