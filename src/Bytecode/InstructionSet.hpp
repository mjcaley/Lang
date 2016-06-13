#pragma once


namespace Lang
{
    enum
    {
        HALT    = 0,
        
        PUSH    = 1,
        POP     = 2,
        
        ADD     = 3,
        SUB     = 4,
        MUL     = 5,
        DIV     = 6,
        MOD     = 7,
        
        JMP     = 8,
        JT      = 9,   // Jump if true
        JF      = 10,   // Jump if false
        
        EQ      = 11,    // Equal
        LT      = 12,    // Less than
        GT      = 13,    // Greater than
        
        
        LOAD    = 14,
        STORE   = 15,
        
        PRNT    = 16,
        
        CALL    = 17,
        RET     = 18,
        
        DUP     = 19
    };
}