#pragma once
#include <map>
#include <string>
#include <vector>


namespace Lang
{
    class LangFile
    {
    /**
     File format:
     (uint*8): magic number
     (uint) version
     (uint) constant count
     0 ... constant count-1: (uint)index; (str)name; (struct/string)value
     uint: function count
     0 ... function count-1: (int)index; (str)name; (int)ip; (int)num of param
    **/
    public:
        static std::unique_ptr<LangFile> create();
        static std::unique_ptr<LangFile> create(const std::string& filename);
        
        template<typename Iterator>
        static bool isValid(Iterator begin, Iterator end)
        {
            auto m_iter = magic_number.begin();
            auto m_end  = magic_number.end();
            
            for (;
                 m_iter != m_end && begin != end;
                 ++m_iter, ++begin)
            {
                if (*m_iter != *begin)
                {
                    return false;
                }
            }
            
            return true;
        }
        
        int version { 1 };
        using name_index_param = std::tuple<std::string, unsigned, int>;
        std::map<unsigned, name_index_param> functions;
        std::map<unsigned, std::string> constants;
        std::vector<int32_t> byte_code;
        
        std::size_t length() const { return byte_code.size(); };
        bool write(const std::string& filename);
        
    private:
        static const std::vector<int32_t> magic_number;
    };
}