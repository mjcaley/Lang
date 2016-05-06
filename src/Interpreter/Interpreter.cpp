#include "Interpreter.hpp"

using namespace Lang;


Interpreter::Interpreter()
{
    identifier_table = IdentifierTable();
    scope_manager = new ScopeManager(identifier_table);
}

Interpreter::~Interpreter()
{
    delete scope_manager;
}