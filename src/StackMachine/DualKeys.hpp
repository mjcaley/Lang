#pragma once
#include <initializer_list>
#include <utility>
#include <vector>


template <typename A, typename B>
class DualKeys
{
public:
    DualKeys() {};
    DualKeys(std::initializer_list< std::pair<A, B> > init) : values(init) {};
    
    A& operator[](B b)
    {
        for (auto& v : values)
        {
            if (v.second == b)
            {
                return v.first;
            }
        }
        
        values.emplace_back( std::make_pair(A(), b) );
        auto& new_value = values.back();
        return new_value.first;
    };
    
    B& operator[](A a)
    {
        for (auto& v : values)
        {
            if (v.first == a)
            {
                return v.second;
            }
        }
        
        values.emplace_back( std::make_pair(a, B()) );
        auto& new_value = values.back();
        return new_value.second;
    };

private:
    std::vector<std::pair<A, B>> values;
};