#include <iostream>
#include <string>
#include <vector>
#include "Interpreter/Types.hpp"


int main()
{
    using namespace Lang;
    
    auto integer = create<Integer>();
    auto ref2 = integer;
    {
        auto ref3 = integer;
    }
    std::cout << "Number of integer refs: " << integer.use_count() << std::endl;
    std::cout << "Dereference integer: " << *integer << std::endl;
    std::cout << "Dereference integer get(): " << *integer.get() << std::endl;
    
    auto integer2 = create<Integer>(3);
    std::cout << "integer2 with constructor argument: " << *integer2 << std::endl;
    
    
    auto dbl = create<Double>(4.2);
    std::cout << "double: " << *dbl << std::endl;
    
    
    auto str = create<String>("Test string");
    std::cout << "string: " << *str << std::endl;
    
    
    return 0;
}