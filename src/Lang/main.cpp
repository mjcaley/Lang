#include "Lang/Lang.hpp"

#include <iostream>
#include <string>
#include <boost/spirit/home/x3.hpp>

int main()
{
    using std::cout;
    using std::endl;
    
    namespace x3 = boost::spirit::x3;
    using namespace Lang;
    
    cout << "Lang 0.1" << std::endl;
    
    std::string program =
        "number : int = 3;";
    
    auto iter = program.begin();
    auto end = program.end();
    AST::Program ast;
    auto& grammar = Grammar::program;
    
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    if (result && iter == end)
    {
        cout << "Success" << endl;
        generate(ast);
    }
    else
    {
        cout << "Failed" << endl;
    }
    
    return 0;
}