#pragma once
#include <vector>
#include "Language/Scope.hpp"
#include "Bytecode/AST.hpp"


namespace Lang { namespace Language {
    
    struct Environment
    {
        std::vector<Scope> scopes { Scope() };
        Bytecode::AST::Program ast;
    };
    
} }