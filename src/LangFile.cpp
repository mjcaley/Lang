#include "LangFile.hpp"
#include "FileFormatException.hpp"
#include <fstream>

using namespace Lang;


std::unique_ptr<LangFile> LangFile::create()
{
    return std::make_unique<LangFile>();
}

std::unique_ptr<LangFile> LangFile::create(const std::string& filename)
{
    using std::istreambuf_iterator;
    
    auto smf = std::make_unique<LangFile>();
    
    std::basic_ifstream<char32_t> in(filename, std::ios::binary);
    if (in.is_open())
    {
        // Check if valid and advance 8 bytes
        bool valid = LangFile::isValid(istreambuf_iterator<char32_t>(in),
                                       istreambuf_iterator<char32_t>());
        if (valid)
        {
            smf->byte_code.insert(smf->byte_code.begin(),
                                  istreambuf_iterator<char32_t>(in),
                                  istreambuf_iterator<char32_t>());
        }
        else
        {
            throw Exception::FileFormatException();
        }
    }
    
    return std::move(smf);
}

bool LangFile::write(const std::string &filename)
{
    std::basic_ofstream<char32_t> out(filename, std::ios::binary);
    if (out.is_open())
    {
        for (auto& m : magic_number)
        {
            out.put(m);
        }
        for (auto& i : byte_code)
        {
            out.put(i);
        }
        
        return true;
    }
    
    return false;
}

const std::vector<int32_t> LangFile::magic_number
    { 0x48, 0x52, 0x42, 0x44, 0x52, 0x47, 0x4E, 0x53 };