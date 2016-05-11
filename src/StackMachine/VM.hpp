#pragma once
#include <cstdint>
#include <iostream>
#include <stack>
#include <string>
#include <vector>


const bool debug { true };

namespace StackMachine
{
    enum InstructionSet
    {
        HALT    = 0x00000000,
        
        PUSH    = 0x00000001,
        POP     = 0x00000002,
        
        ADD     = 0x00000003,
        SUB     = 0x00000004,
        MUL     = 0x00000005,
        DIV     = 0x00000006,
        MOD     = 0x00000007,
        
        JMP     = 0x00000008,
        
        LOAD    = 0x00000009,
        STORE   = 0x0000000A,
        
        PRNT    = 0x0000000B
    };
    
    class VM
    {
    public:
        VM(int32_t memory_size = 1000000)
        {
            memory.reserve(memory_size);
        };
        
        void loadProgram(std::vector<int32_t> p) { program = p; };
        
        void run();
        
    private:
        unsigned ip { 0 };  // Instruction pointer
        unsigned fp;        // Frame pointer
        bool running { false };

        std::vector<int32_t> program { 0 };
        std::stack<int32_t> stack;
        std::vector<int32_t> memory;
        
        // Arithmetic
        void add();
        void subtract();
        void multiply();
        void divide();
        void modulus();
        
        // Control flow
        void jump();
        
        void load();
        void store();
        
        void print();
    };
}