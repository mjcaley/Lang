#include <iostream>
#include <string>
#include <vector>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>
#include "Interpreter/ReferenceTable.hpp"


int main()
{
    using namespace Lang;
    
    auto ref_table = ReferenceTable();
    auto ref = ref_table.create<Integer>();
    auto ref2 = ref;
    {
        auto ref3 = ref;
    }
    std::cout << "Number of refs: " << ref.use_count() << std::endl;
    std::cout << *ref << std::endl;
    std::cout << *ref.get() << std::endl;
    
    auto r = std::make_shared<Integer>(3);
    std::cout << *r << std::endl;
    
    ref_table.create<Integer>();
    ref_table.create<Integer>();
    ref_table.create<Integer>();
    
    std::cout << ref_table.size() << std::endl;
    
    std::cout << ref_table.size() << std::endl;
    
    
    return 0;
}