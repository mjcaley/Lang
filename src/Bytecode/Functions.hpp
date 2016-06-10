#pragma once
#include "LangFile.hpp"
#include "Bytecode/Visitors.hpp"


namespace Lang { namespace Bytecode {
    
    bool compile(const AST::Program &instructions, LangFile& file)
    {
        std::map<std::string, int32_t> label_map;
        
        AST::LabelPreprocessor label_preprocessor(label_map);
        for (auto& ast : instructions)
        {
            boost::apply_visitor(label_preprocessor, ast);
        }
        
        AST::CodeGenerator generator(file.byte_code, label_map);
        for (auto& ast : instructions)
        {
            boost::apply_visitor(generator, ast);
        }
        
        return true;
    }
    
} }