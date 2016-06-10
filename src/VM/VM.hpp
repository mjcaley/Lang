#pragma once
#include <boost/algorithm/string/join.hpp>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <map>
#include <stack>
#include <string>
#include <vector>
#include "LangFile.hpp"
#include "VM/DualKeys.hpp"
#include "VM/Stack.hpp"


namespace Lang { namespace VM {
    
    using i32 = int32_t;
    
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
    
    static DualKeys<i32, std::string> instruction_strings
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
        VM() { init(); }
        
        bool debug { false };
        
        void loadProgram(std::unique_ptr<LangFile> program);
        
        bool run();
        
    private:
        unsigned ip { 0 };  // Instruction pointer
        bool running { false };

        std::unique_ptr<LangFile> program;
        
        Stack<std::map<unsigned, i32>>  frame;
        Stack<i32>                      call;
        Stack<i32>                      data;
        
        void init();
        
        // Arithmetic
        void add_op();
        void subtract_op();
        void multiply_op();
        void divide_op();
        void modulus_op();
        
        // Control flow
        void jump_op();
        void jump_if_true_op();
        void jump_if_false_op();
        
        void equal_op();
        void less_than_op();
        void greater_than_op();
        
        void call_op();
        void ret_op();
        
        void load_op();
        void store_op();
        
        void print_op();
        
        void dup_op();
        
        void nullary_debug_message(int ip);
        void unary_debug_message(int ip);
        void binary_debug_message(int ip);
        
        template <typename Iterator>
        void debug_message(Iterator begin, Iterator end)
        {
            using std::cout;
            using std::setw;
            using std::left;
            using std::right;
            using std::endl;
            using std::to_string;
            using boost::algorithm::join;
            
            
            std::string lcolumn, mcolumn, rcolumn;
            
            lcolumn = instruction_strings[*begin] + ' ';
            {
                begin++;
                std::vector<std::string> operands;
                for (; begin != end; ++begin)
                {
                    operands.emplace_back(to_string(*begin));
                }
                lcolumn += join(operands, " ");
            }
            
            mcolumn = "Data stack: [ ";
            {
                std::vector<std::string> data_values;
                for (const auto& i : data)
                {
                    data_values.emplace_back(to_string(i));
                }
                mcolumn += join(data_values, ", ");
            }
            mcolumn += " ] ";
            
            rcolumn = "Call stack: [ ";
            {
                std::vector<std::string> call_values;
                for (const auto& i : call)
                {
                    call_values.emplace_back(to_string(i));
                }
                rcolumn += join(call_values, ", ");
            }
            rcolumn += " ] ";
            
            std::cout << setw(20) << left << lcolumn
            << setw(40) << left << mcolumn
            << setw(20) << left << rcolumn
            << endl;
        };
    };
    
} }