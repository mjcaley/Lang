#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
#include "Types.hpp"
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>


namespace Lang
{
    using RefVariant = boost::variant<Reference<Integer>,
                                      Reference<Double>,
                                      Reference<String>
                                      //Reference<Function>,
                                      //Reference<Struct>,
                                      //Reference<Trait>
    >;
    
    class ReferenceTable
    {
        class ifZeroRef : public boost::static_visitor<bool>
        {
        public:
            template<typename T>
            bool operator()(T& operand) const
            {
                return operand.getRefs() == 0;
            }
        };
        
    public:
        template<typename T, typename ... Arg>
        Reference<T>& create(Arg... arg)
        {
            table.emplace_back(Reference<T>(arg...));
            return boost::get<Reference<T>>(table.back());
        }

        // Table management
        void clear()
        {
            table.clear();
        };
        
        void garbage_collect()
        {
            auto iter = table.begin();
            auto end = table.end();
            auto ref_test = [&](RefVariant ref){ return boost::apply_visitor(ReferenceTable::ifZeroRef(), ref); };
            
            table.erase(std::remove_if(iter, end, ref_test ), end);
        };
        
        // Status
        size_t size() const { return table.size(); };
        bool empty() const { return table.empty(); };
        
    private:
        std::vector<RefVariant> table;
    };
}