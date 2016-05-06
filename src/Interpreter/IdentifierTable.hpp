#pragma once
#include "LangObject.hpp"
#include <vector>


namespace Lang
{
    class IdentifierTable
    {
    public:
        ~IdentifierTable()
        {
            for (auto i : identifiers)
            {
                delete i;
            }
        };
        
        LangObject* newObject()
        {
            auto object = new LangObject;
            identifiers.emplace_back(object);
            
            return object;
        };
        
        void deleteObject(LangObject* object)
        {
            identifiers.erase(std::remove(identifiers.begin(), identifiers.end(), object), identifiers.end());
        };
        
        
    private:
        std::vector<LangObject*> identifiers;
    };
}