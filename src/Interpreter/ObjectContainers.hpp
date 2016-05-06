#pragma once
#include <string>


namespace Lang
{
    template<typename T>
    struct ObjectContainer
    {
        T value;
    };
    
    // Specialize for default values
    template<>
    struct ObjectContainer<bool>
    {
        bool value = false;
    };
    
    template<>
    struct ObjectContainer<int>
    {
        long int value { 0 };
    };
    
    template<>
    struct ObjectContainer<long int>
    {
        long int value { 0 };
    };
    
    template<>
    struct ObjectContainer<double>
    {
        double value { 0 };
    };
}