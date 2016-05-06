#include <iostream>
#include <boost/spirit/home/x3.hpp>
#include "Interpreter/Interpreter.hpp"

using namespace Lang;


int main()
{
    auto lang = Interpreter();
    
    auto sm = lang.getScopeManager();
    auto s = sm->getFrontScope();
    auto i = sm->createInt(s);
    std::cout << i->toString();
    
    return 0;
}