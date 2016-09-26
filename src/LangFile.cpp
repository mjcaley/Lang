#include "LangFile.hpp"
#include "FileFormatException.hpp"
#include "FileNotFoundException.hpp"
#include <fstream>

using namespace Lang;

using i32 = int32_t;


std::unique_ptr<LangFile> LangFile::create()
{
    return std::make_unique<LangFile>();
}

std::unique_ptr<LangFile> LangFile::create(const std::string& filename)
{
    using std::istreambuf_iterator;
    
    auto smf = std::make_unique<LangFile>();
    
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open())
    {
        // Check if valid and advance 8 bytes
        bool valid = LangFile::isValid(istreambuf_iterator<char>(in),
                                       istreambuf_iterator<char>());
        if (valid)
        {
            smf->byte_code.insert(smf->byte_code.begin(),
                                  istreambuf_iterator<char>(in),
                                  istreambuf_iterator<char>());
        }
        else
        {
            throw Exception::FileFormatException();
        }
    }
    else
    {
        throw Exception::FileNotFoundException(filename);
    }
    
    return smf;
}

bool LangFile::write(const std::string &filename)
{
    std::ofstream out(filename, std::ios::binary);
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

const std::vector<i32> LangFile::magic_number
    { 0x48, 0x52, 0x42, 0x44, 0x52, 0x47, 0x4E, 0x53 };
