#include "LangObject.hpp"


std::string Lang::LangTypeToString(LangType type)
{
    switch (type)
    {
        case LangType::INT:
            return "INT";
        case LangType::DOUBLE:
            return "DOUBLE";
        case LangType::BOOL:
            return "BOOL";
        case LangType::STRING:
            return "STRING";
        case LangType::FUNCTION:
            return "FUNCTION";
    }
}