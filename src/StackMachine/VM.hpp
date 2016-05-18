#pragma once
#include <cstdint>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include "DualKeys.hpp"


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
        
        EQ      = 0x0000000B,    // Equal
        LT      = 0x0000000C,    // Less than
        GT      = 0x0000000D,    // Greater than
        
        
        LOAD    = 0x0000000E,
        STORE   = 0x0000000F,
        
        PRNT    = 0x00000010,
        
        CALL    = 0x00000011,
        RET     = 0x00000012,
        
        DUP     = 0x00000013
    };
    
    static DualKeys<int32_t, std::string> instruction_strings
    {
        { HALT, "HALT" },   { PUSH, "PUSH" },   { POP, "POP" },
        { ADD, "ADD" },     { SUB, "SUB" },     { MUL, "MUL" },
        { DIV, "DIV" },     { MOD, "MOD" },     { JMP, "JMP" },
        { JT, "JT" },       { JF, "JF" },       { EQ, "EQ" },
        { LT, "LT" },       { GT, "GT" },       { LOAD, "LOAD" },
        { STORE, "STORE" }, { PRNT, "PRNT" },   { CALL, "CALL" },
        { RET, "RET" },     { DUP, "DUP" }
    };

    class VM
    {
    public:
        void loadProgram(std::vector<int32_t> p) { program = p; };
        
        bool run();
        
    private:
        unsigned ip { 0 };  // Instruction pointer
        bool running { false };

        std::vector<int32_t> program { 0 };
        std::stack<int32_t> call_stack;
        std::stack<int32_t> data_stack;
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
        
        void equal();
        void less_than();
        void greater_than();
        
        void call();
        void ret();
        
        void load();
        void store();
        
        void print();
        
        void dup();
        
        void nullaryDebugMessage(int ip);
        void unaryDebugMessage(int ip);
        void binaryDebugMessage(int ip);
        void debugMessage(std::vector<int32_t>::const_iterator begin,
                          std::vector<int32_t>::const_iterator end);
    };
}