#pragma once
#include <vector>


namespace StackMachine
{
    template <typename T>
    class Stack
    {
    public:
        Stack(std::size_t reserve = 100)
        {
            stack.reserve(reserve);
        }
        
        void    pop()           { stack.pop_back(); }
        void    push(T value)   { stack.push_back(value); }
        void    push()          { stack.push_back(T()); }
        T&      top_of_stack()  { return stack.back(); }
        T&      tos()           { return top_of_stack(); };
        
        void clear() { stack.clear(); };
        
        typename std::vector<T>::iterator iterator;
        typename std::vector<T>::const_iterator const_iterator;
        
        typename std::vector<T>::iterator begin()
        {
            return stack.begin();
        };
        
        typename std::vector<T>::iterator end()
        {
            return stack.end();
        };
        
        typename std::vector<T>::const_iterator begin() const
        {
            return stack.cbegin();
        };
        
        typename std::vector<T>::const_iterator end() const
        {
            return stack.cend();
        };
        
        
    private:
        std::vector<T> stack;
    };
}