#include "VM.hpp"
#include <iostream>

using namespace StackMachine;


void VM::run()
{
    running = true;
    while(running)
    {
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

void VM::add()
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

void VM::subtract()
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

void VM::multiply()
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

void VM::divide()
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

void VM::modulus()
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

void VM::jump()
{
    ++ip;   // Advance to data
    ip = program[ip];
    
    if (debug)
    {
        std::cout << "JMP " << ip << std::endl;
    }
}

void VM::load()
{
    ++ip;   // Advance to data
    stack.push( memory[program[ip]] );
    ++ip;
    
    if (debug)
    {
        std::cout << "LOAD " << stack.top() << std::endl;
    }
}

void VM::store()
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

void VM::print()
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

