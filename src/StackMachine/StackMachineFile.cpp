#include "StackMachineFile.hpp"
#include <fstream>

using namespace StackMachine;


std::unique_ptr<StackMachineFile> StackMachineFile::create()
{
    return std::make_unique<StackMachineFile>();
}

std::unique_ptr<StackMachineFile> StackMachineFile::create(const std::string& filename)
{
    using std::istreambuf_iterator;
    
    auto smf = std::make_unique<StackMachineFile>();
    
    std::ifstream in(filename, std::ios::binary);
    if (in.is_open())
    {
        // Check if valid and advance 8 bytes
        bool valid = StackMachineFile::isValid(istreambuf_iterator<char>(in),
                                               istreambuf_iterator<char>());
        if (valid)
        {
            smf->byte_code.insert(smf->byte_code.begin(),
                                  istreambuf_iterator<char>(in),
                                  istreambuf_iterator<char>());
        }
        else
        {
            return nullptr;
        }
    }
    
    return std::move(smf);
}

bool StackMachineFile::write(const std::string &filename)
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

const std::vector<int32_t> StackMachineFile::magic_number
    { 0x48, 0x52, 0x42, 0x44, 0x52, 0x47, 0x4E, 0x53 };