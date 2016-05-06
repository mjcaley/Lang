#pragma once
#include <memory>
#include "Scope.hpp"


namespace Lang
{
    class Interpreter
    {
    public:
        Interpreter();
        ~Interpreter();
        
        // TEMP
        ScopeManager* getScopeManager() { return scope_manager; };
        
    private:
        IdentifierTable identifier_table;
        ScopeManager* scope_manager;
    };
}