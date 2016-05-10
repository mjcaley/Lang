#include "StackMachine.hpp"
#include <iostream>
#include <boost/variant.hpp>

using namespace Lang;


void StackMachine::run()
{
    running = true;
    while(running)
    {
        //std::cout << "ip @ " << ip << std::endl;
        switch(program[ip])
        {
            case HALT:
                running = false;
                
                if (debug)
                {
                    std::cout << "HALT" << std::endl;
                }
                break;
            case PUSH:
                ++ip;   // Advance to data
                stack.push(program[ip]);
                ++ip;
                
                if (debug)
                {
                    std::cout << "PUSH " << std::endl;
                }
                break;
            case POP:
                stack.pop();
                ++ip;
                
                if (debug)
                {
                    std::cout << "POP" << std::endl;
                }
                break;
            case ADD:
                add();
                break;
            case SUB:
                subtract();
                break;
            case MUL:
                multiply();
                break;
            case DIV:
                divide();
                break;
            case MOD:
                modulus();
                break;
            case JMP:
                jump();
                break;
            case LOAD:
                load();
                break;
            case STORE:
                store();
                break;
            case PRNT:
                print();
                break;
            default:
                running = false;
                break;
        }
    }
}

void StackMachine::add()
{
    const auto operand1 = stack.top();
    stack.pop();
    const auto operand2 = stack.top();
    stack.pop();
    stack.push( operand1 + operand2 );
    ++ip;
    
    if (debug)
    {
        std::cout << "ADD " << operand1 << " " << operand2 << " = " << stack.top() << std::endl;
    }
}

void StackMachine::subtract()
{
    const auto operand1 = stack.top();
    stack.pop();
    const auto operand2 = stack.top();
    stack.pop();
    stack.push( operand2 - operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "SUB " << operand2 << " " << operand1 << " = " << stack.top() << std::endl;
    }
}

void StackMachine::multiply()
{
    const auto operand1 = stack.top();
    stack.pop();
    const auto operand2 = stack.top();
    stack.pop();
    stack.push(operand1 * operand2);
    ++ip;
    
    if (debug)
    {
        std::cout << "MUL " << operand1 << " " << operand2 << " = " << stack.top() << std::endl;
    }
}

void StackMachine::divide()
{
    const auto operand1 = stack.top();
    stack.pop();
    const auto operand2 = stack.top();
    stack.pop();
    stack.push( operand2 / operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "DIV " << operand2 << " " << operand1 << " = " << stack.top() << std::endl;
    }
}

void StackMachine::modulus()
{
    const auto operand1 = stack.top();
    stack.pop();
    const auto operand2 = stack.top();
    stack.pop();
    stack.push( operand2 % operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "MOD " << operand2 << " " << operand1 << " = " << stack.top() << std::endl;
    }
}

void StackMachine::jump()
{
    ++ip;   // Advance to data
    ip = program[ip];
    
    if (debug)
    {
        std::cout << "JMP " << ip << std::endl;
    }
}

void StackMachine::load()
{
    ++ip;   // Advance to data
    stack.push( memory[program[ip]] );
    ++ip;
    
    if (debug)
    {
        std::cout << "LOAD " << stack.top() << std::endl;
    }
}

void StackMachine::store()
{
    ++ip;   // Advance to data
    const auto value = stack.top();
    memory[program[ip]] = value;
    stack.pop();
    ++ip;
    
    if (debug)
    {
        std::cout << "STORE " << value << std::endl;
    }
}

void StackMachine::print()
{
    const auto operand = stack.top();
    stack.pop();
    std::cout << operand << std::endl;
    ++ip;
    
    if (debug)
    {
        std::cout << "PRNT" << std::endl;
    }
}

int main()
{
    auto sm = StackMachine();
    sm.loadProgram( {
        PUSH, 10, PUSH, 16, ADD,    // 10+16
        PRNT,
        PUSH, 60, PUSH, 18, SUB,    // 60-18
        PRNT,
        PUSH, 4, PUSH, 3, MUL,      // 4*3
        PRNT,
        JMP, 26,                    // Jump to address 23
        0, 0, 0, 0, 0, 0,           // Garbage data
        PUSH, 12, PUSH, 3, DIV,     // 12/3
        PRNT,
        PUSH, 11, PUSH, 2, MOD,     // 11%2
        PRNT,
        PUSH, 32, STORE, 0,         // Save 32 to memory address 0
        LOAD, 0, PRNT,              // Load from memory address 0 and print
        HALT                        // Halt
    } );
    //sm.run();
    
    //std::string program = "PUSH 3 PUSH 4 ADD HALT";
    
    std::string program = "PUSH 3 PUSH 12 ADD HALT";
    auto iter = program.begin();
    auto end = program.end();
    std::vector<int32_t> result;
    auto& grammar = sm_grammar::program;
    
    bool r = boost::spirit::x3::phrase_parse(iter, end, grammar, boost::spirit::x3::space, result);
    
    if (r)
    {
        std::cout << "Success\n";
        
        for (auto& i : result)
            std::cout << i << std::endl;
    }
    else
    {
        std::cout << "Failed" << std::endl;
    }
    
    return 0;
}