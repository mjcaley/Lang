#pragma once
#include <string>
#include "Bytecode/AST.hpp"
#include "Language/AST.hpp"


namespace Lang { namespace Language {
   
    struct Scope
    {
        Bytecode::AST::Program scoped_ast {};
        std::map<std::string, std::pair<int, AST::Type>> variables;
    };
    
} }