#pragma once
#include <algorithm>
#include <iostream>
#include <memory>
#include <vector>
#include "Types.hpp"
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>


namespace Lang
{
    class ReferenceTable
    {
    public:
        template<typename T, typename ... Arg>
        std::shared_ptr<T> create(Arg... arg)
        {
            table.emplace_back(std::make_shared<T>(arg...));
            return boost::get<std::shared_ptr<T>>(table.back());
        }

        // Table management
        void clear()
        {
            table.clear();
        };
        
        // Status
        size_t size() const { return table.size(); };
        bool empty() const { return table.empty(); };
        
    private:
        std::vector<Value> table;
    };
}