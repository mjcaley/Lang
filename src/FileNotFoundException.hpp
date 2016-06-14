#pragma once
#include <stdexcept>
#include <string>


namespace Lang { namespace Exception {
    
    class FileNotFoundException : public std::runtime_error
    {
    public:
        FileNotFoundException(const std::string& filename) :
            runtime_error("File " + filename + " not found") {};
    };
    
} }