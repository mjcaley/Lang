#pragma once
#include <map>
#include <string>
#include <vector>
#include <boost/optional.hpp>
#include "LangObject.hpp"
#include "IdentifierTable.hpp"


namespace Lang
{
    class Scope;
    
    class ScopeManager
    {
    public:
        ScopeManager(IdentifierTable& identifier_table) : identifier_table(identifier_table)
        {
            pushScope();
        };
        
        void popScope();
        Scope* pushScope();
        Scope* getFrontScope();
        Scope* getBackScope();
        
        LangObject* createBool(Scope* scope);
        LangObject* createInt(Scope* scope);
        LangObject* createString(Scope* scope);
        LangObject* createFunction(Scope* scope);
        
    private:
        IdentifierTable& identifier_table;
        std::vector<Scope> scopes;
    };
    
    class Scope
    {
    public:
        Scope() = default;
        ~Scope();
        
        std::vector<Scope*> getChildren();
        void addChild(Scope* child);
        void removeChild(Scope* child);
        
        Scope* getParent();
        void setParent(Scope* parent);
        
        void addVariable(std::string name, LangObject* object);
        
    private:
        Scope* parent = nullptr;
        std::vector<Scope*> children;
        
        std::map<std::string, LangObject*> variables;
    };
}