#pragma once
#include <iostream>
#include <string>
#include <tuple>
#include <typeindex>
#include <typeinfo>
#include <boost/variant.hpp>


namespace Lang
{
    enum class LangType
    {
        INT,
        DOUBLE,
        BOOL,
        STRING,
        FUNCTION
        // User defined object
    };
    
    std::string LangTypeToString(LangType type);
    
    class LangObject
    {
    public:
        LangObject() = default;
        ~LangObject() = default;
    
        using TypeValue = boost::variant<long int, double, std::string, bool>;
//        struct visitor : public boost::static_visitor<bool>
//        {
//            template<typename T typename U>
//            void operator()(T& t, U& u) const { std::cout << t << u << '\n'; };
//        };
        
        inline void incRef() { reference_count++; };
        inline void decRef() { reference_count--; };
        
        int getRefCount() const { return reference_count; };
        
        std::tuple<TypeValue, LangType> getObject() const
        {
            return std::make_tuple(value, type);
        };
        
        TypeValue getObjectValue() const { return value; };
        LangType getObjectType() const { return type; };
        template<typename T>
        void setObject(T v)
        {
            if (typeid(v) == typeid(bool))
            {
                value = v;
                type = LangType::BOOL;
            }
            else if (typeid(v) == typeid(long))
            {
                type = LangType::INT;
            }
            else if (typeid(v) == typeid(double))
            {
                type = LangType::DOUBLE;
            }
            else if (typeid(v) == typeid(std::string))
            {
                type = LangType::STRING;
            }
        };
        
        std::string toString()
        {
            std::string str = "LangObject [RefCount: " +
                              std::to_string(reference_count) +
                              "] [Type: " +
                              LangTypeToString(type) +
                              "]\n";
            return str;
        }
        
    private:
        int reference_count = 0;
        boost::variant<long, double, std::string, bool> value;
        LangType type;
    };
}