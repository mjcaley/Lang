#pragma once
#include <cstdint>
#include <iostream>
#include <map>
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
        JT      = 0x00000009,   // Jump if true
        JF      = 0x0000000A,   // Jump if false
        
        
        LOAD    = 0x0000000B,
        STORE   = 0x0000000C,
        
        PRNT    = 0x0000000D,
        
        CALL    = 0x0000000E,
        RET     = 0x0000000F
    };
    
    class VM
    {
    public:
        void loadProgram(std::vector<int32_t> p) { program = p; };
        
        bool run();
        
    private:
        unsigned ip { 0 };  // Instruction pointer
        unsigned fp { 0 };  // Frame pointer
        bool running { false };

        std::vector<int32_t> program { 0 };
        std::stack<int32_t> call_stack;
        std::stack<int32_t> stack;
        std::map<unsigned, int32_t> memory;
        
        void clearMemory();
        
        // Arithmetic
        void add();
        void subtract();
        void multiply();
        void divide();
        void modulus();
        
        // Control flow
        void jump();
        void jump_if_true();
        void jump_if_false();
        
        void call();
        void ret();
        
        void load();
        void store();
        
        void print();
    };
}