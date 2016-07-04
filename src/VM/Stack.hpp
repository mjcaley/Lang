#pragma once
#include <vector>


namespace Lang { namespace VM {
    
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
        typename std::vector<T>::reverse_iterator reverse_iterator;
        typename std::vector<T>::const_reverse_iterator const_reverse_iterator;
        
        typename std::vector<T>::iterator begin()
        {
            return stack.begin();
        };
        
        typename std::vector<T>::iterator end()
        {
            return stack.end();
        };
        
        typename std::vector<T>::const_iterator cbegin() const
        {
            return stack.cbegin();
        };
        
        typename std::vector<T>::const_iterator begin() const
        {
            return cbegin();
        };
        
        typename std::vector<T>::const_iterator cend() const
        {
            return stack.cend();
        };
        
        typename std::vector<T>::const_iterator end() const
        {
            return cend();
        };
        
        
        typename std::vector<T>::reverse_iterator rbegin()
        {
            return stack.rbegin();
        };
        
        typename std::vector<T>::reverse_iterator rend()
        {
            return stack.rend();
        };
        
        typename std::vector<T>::const_reverse_iterator crbegin() const
        {
            return stack.crbegin();
        };
        
        typename std::vector<T>::const_reverse_iterator rbegin() const
        {
            return crbegin();
        };
        
        typename std::vector<T>::const_reverse_iterator crend() const
        {
            return stack.crend();
        };
        
        typename std::vector<T>::const_reverse_iterator rend() const
        {
            return crend();
        };
        
        
    private:
        std::vector<T> stack;
    };
    
} }