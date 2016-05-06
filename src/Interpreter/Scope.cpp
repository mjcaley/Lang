#include "Scope.hpp"

using namespace Lang;


void ScopeManager::popScope()
{
    if (&scopes.back() != &scopes.front())
    {
        // Only pop if this isn't the root scope
        scopes.pop_back();
    }
};

Scope* ScopeManager::pushScope()
{
    if (!scopes.empty())
    {
        auto& back_scope = scopes.back();
        scopes.emplace_back(Scope());
        auto& new_scope = scopes.back();
        
        back_scope.addChild(&new_scope);
        new_scope.setParent(&back_scope);
    }
    else
    {
        // Create root scope
        scopes.emplace_back(Scope());
    }
    return getFrontScope();
};

Scope* ScopeManager::getFrontScope()
{
    return &scopes.front();
}

Scope* ScopeManager::getBackScope()
{
    return &scopes.back();
};

LangObject* ScopeManager::createBool(Scope* scope)
{
    auto object = identifier_table.newObject();
    scope->addVariable("Test", object);
    object->incRef();
    object->setObject(true);
    
    return object;
}

LangObject* ScopeManager::createInt(Scope* scope)
{
    auto object = identifier_table.newObject();
    scope->addVariable("Test", object);
    object->incRef();
    object->setObject(0);
    
    return object;
}

LangObject* ScopeManager::createString(Scope* scope)
{
    auto object = identifier_table.newObject();
    scope->addVariable("Test", object);
    object->incRef();
    object->setObject("test");
    
    return object;
}

LangObject* ScopeManager::createFunction(Scope* scope)
{
    auto object = identifier_table.newObject();
    scope->addVariable("Test", object);
    object->incRef();
    object->setObject(0); // TODO: Figure out how to make functions
    
    return object;
}


Scope::~Scope()
{
    for (auto& var : variables)
    {
        var.second->decRef();
    }
};

std::vector<Scope*> Scope::getChildren()
{
    return children;
};

void Scope::addChild(Scope* child)
{
    children.emplace_back(child);
};

void Scope::removeChild(Scope* child)
{
    children.erase(std::remove(children.begin(), children.end(), child), children.end());
};

Scope* Scope::getParent()
{
    return parent;
};

void Scope::setParent(Scope* parent)
{
    this->parent = parent;
};

void Scope::addVariable(std::string name, LangObject* object)
{
    variables[name] = object;
}