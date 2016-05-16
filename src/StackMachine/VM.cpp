#include "VM.hpp"
#include <iostream>

using namespace StackMachine;


bool VM::run()
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
                data_stack.push(program[ip]);
                ++ip;
                
                if (debug)
                {
                    std::cout << "PUSH " << std::endl;
                }
                break;
            case POP:
                data_stack.pop();
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
            case JT:
                jump_if_true();
                break;
            case JF:
                jump_if_false();
                break;
            case EQ:
                equal();
                break;
            case LT:
                less_than();
                break;
            case GT:
                greater_than();
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
            case CALL:
                call();
                break;
            case RET:
                ret();
                break;
            case DUP:
                dup();
                break;
            default:
                running = false;
                break;
        }
    }
    
    clearMemory();
    return true;
}

void VM::clearMemory()
{
    memory.clear();
}

void VM::add()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    data_stack.push( operand1 + operand2 );
    ++ip;
    
    if (debug)
    {
        std::cout << "ADD " << operand1 << " " << operand2 << " = " << data_stack.top() << std::endl;
    }
}

void VM::subtract()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    data_stack.push( operand2 - operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "SUB " << operand2 << " " << operand1 << " = " << data_stack.top() << std::endl;
    }
}

void VM::multiply()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    data_stack.push(operand1 * operand2);
    ++ip;
    
    if (debug)
    {
        std::cout << "MUL " << operand1 << " " << operand2 << " = " << data_stack.top() << std::endl;
    }
}

void VM::divide()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    data_stack.push( operand2 / operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "DIV " << operand2 << " " << operand1 << " = " << data_stack.top() << std::endl;
    }
}

void VM::modulus()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    data_stack.push( operand2 % operand1 );
    ++ip;
    
    if (debug)
    {
        std::cout << "MOD " << operand2 << " " << operand1 << " = " << data_stack.top() << std::endl;
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

void VM::jump_if_true()
{
    ++ip;   // Advance to data
    const auto test = data_stack.top();
    data_stack.pop();
    if (test == true)
    {
        ip = program[ip];
    }
    else
    {
        ++ip;
    }
    
    if (debug)
    {
        std::cout << "JT " << ip << " to " << ip << std::endl;
    }
}

void VM::jump_if_false()
{
    ++ip;   // Advance to data
    const auto test = data_stack.top();
    data_stack.pop();
    if (test == false)
    {
        ip = program[ip];
    }
    else
    {
        ++ip;
    }
    
    if (debug)
    {
        std::cout << "JF " << ip << " to " << ip << std::endl;
    }
}

void VM::equal()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    
    if (operand1 == operand2)
    {
        data_stack.push(true);
    }
    else
    {
        data_stack.push(false);
    }
    ++ip;
    
    if (debug)
    {
        std::cout << "EQ " << std::endl;
    }
}

void VM::less_than()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    
    if (operand2 < operand1)
    {
        data_stack.push(true);
    }
    else
    {
        data_stack.push(false);
    }
    ++ip;
    
    if (debug)
    {
        std::cout << "LT " << std::endl;
    }
}

void VM::greater_than()
{
    const auto operand1 = data_stack.top();
    data_stack.pop();
    const auto operand2 = data_stack.top();
    data_stack.pop();
    
    if (operand2 > operand1)
    {
        data_stack.push(true);
    }
    else
    {
        data_stack.push(false);
    }
    ++ip;
    
    if (debug)
    {
        std::cout << "GT " << std::endl;
    }
}

void VM::call()
{
    ++ip;   // Advance to call address
    const auto address = program[ip];
    ++ip;   // Advance to number of arguments
    const auto nargs = program[ip];
    data_stack.push(nargs);
    call_stack.push(++ip);
    ip = address;
    
    if(debug)
    {
        std::cout << "CALL " << std::endl;
    }
}

void VM::ret()
{
    const auto ret_address = call_stack.top();
    call_stack.pop();
    ip = ret_address;
    
    if (debug)
    {
        std::cout << "RET" << std::endl;
    }
}

void VM::load()
{
    ++ip;   // Advance to data
    data_stack.push( memory[program[ip]] );
    ++ip;
    
    if (debug)
    {
        std::cout << "LOAD " << data_stack.top() << std::endl;
    }
}

void VM::store()
{
    ++ip;   // Advance to data
    const auto value = data_stack.top();
    memory[program[ip]] = value;
    data_stack.pop();
    ++ip;
    
    if (debug)
    {
        std::cout << "STORE " << value << std::endl;
    }
}

void VM::print()
{
    const auto operand = data_stack.top();
    data_stack.pop();
    std::cout << operand << std::endl;
    ++ip;
    
    if (debug)
    {
        std::cout << "PRNT" << std::endl;
    }
}

void VM::dup()
{
    data_stack.push(data_stack.top());
    ++ip;
    
    if (debug)
    {
        std::cout << "DUP" << std::endl;
    }
}