#pragma once
#include <stdexcept>
#include <string>


namespace Lang { namespace Exception {
   
    class FileFormatException : public std::runtime_error
    {
    public:
        FileFormatException() : runtime_error("Invalid file format") {};
    };
    
} }