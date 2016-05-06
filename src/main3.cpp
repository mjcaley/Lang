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
    auto& ref = ref_table.create<Integer>();
    ref.incrementRef();
    ref.data.set(42);
    auto& s_ref = ref.data;
    std::cout << ref << std::endl;
    std::cout << s_ref() << std::endl;
    ref.data++;
    s_ref++;
    std::cout << ref.data() << std::endl;
    
    auto r = Reference<Integer>(3);
    std::cout << r << std::endl;
    
//    std::cout << ref.data.get() << std::endl;
//    ref.data.set(ref.data.get() + 42);
//    std::cout << ref.data.get() << std::endl;
//    std::cout << (int)ref.data.getType() << std::endl;
    
    ref_table.create<Integer>();
    ref_table.create<Integer>();
    ref_table.create<Integer>();
    
    std::cout << ref_table.size() << std::endl;
    
    ref_table.garbage_collect();
    
    std::cout << ref_table.size() << std::endl;
    
    
    return 0;
}