#include "VM.hpp"
#include <iomanip>
#include <iostream>

using namespace StackMachine;


bool VM::run()
{
    running = true;
    while(running && ip < program.size())
    {
        switch(program[ip])
        {
            case HALT:
                running = false;
                
                if (debug)
                {
                    nullaryDebugMessage(ip);
                }
                break;
            case PUSH:
                ++ip;   // Advance to data
                data_stack.push(program[ip]);
                ++ip;
                
                if (debug)
                {
                    unaryDebugMessage(ip-2);
                }
                break;
            case POP:
                data_stack.pop();
                ++ip;
                
                if (debug)
                {
                    nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
    }
}

void VM::jump()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to data
    ip = program[ip];
    
    if (debug)
    {
        unaryDebugMessage(orig_ip);
    }
}

void VM::jump_if_true()
{
    auto orig_ip = ip;
    
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
        unaryDebugMessage(orig_ip);
    }
}

void VM::jump_if_false()
{
    auto orig_ip = ip;
    
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
        unaryDebugMessage(orig_ip);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
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
        nullaryDebugMessage(ip-1);
    }
}

void VM::call()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to call address
    const auto address = program[ip];
    ++ip;   // Advance to number of arguments
    const auto nargs = program[ip];
    data_stack.push(nargs);
    call_stack.push(++ip);
    ip = address;
    
    if(debug)
    {
        binaryDebugMessage(orig_ip);
    }
}

void VM::ret()
{
    auto orig_ip = ip;
    
    const auto ret_address = call_stack.top();
    call_stack.pop();
    ip = ret_address;
    
    if (debug)
    {
        nullaryDebugMessage(orig_ip);
    }
}

void VM::load()
{
    ++ip;   // Advance to data
    data_stack.push( memory[program[ip]] );
    ++ip;
    
    if (debug)
    {
        unaryDebugMessage(ip-2);
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
        unaryDebugMessage(ip-2);
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
        nullaryDebugMessage(ip-1);
    }
}

void VM::dup()
{
    data_stack.push(data_stack.top());
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::nullaryDebugMessage(int ip)
{
    const auto begin = program.begin() + ip;
    const auto end = program.begin() + (ip + 1);
    debugMessage(begin, end);
}

void VM::unaryDebugMessage(int ip)
{
    const auto begin = program.begin() + ip;
    const auto end = program.begin() + (ip + 2);
    debugMessage(begin, end);
}

void VM::binaryDebugMessage(int ip)
{
    const auto begin = program.begin() + ip;
    const auto end = program.begin() + (ip + 3);
    debugMessage(begin, end);
}

void VM::debugMessage(std::vector<int32_t>::const_iterator iter,
                      std::vector<int32_t>::const_iterator end)
{
    using std::cout;
    using std::setw;
    using std::left;
    using std::right;
    using std::endl;
    
    // Print instructions and operands
    cout << setw(12) << left << instruction_strings[*iter] << ' ';
    iter++;
    for (; iter != end; ++iter)
    {
        cout << left << *iter << setw(25);
    }
    
    // Print top of data and call stack
    cout << setw(25) << right << "Call stack: [ ";
    if (!data_stack.empty())
    {
        cout << data_stack.top();
    }
    else
    {
        cout << ' ';
    }
    cout << " ] ";
    
    cout << "Data stack: [ ";
    if (!call_stack.empty())
    {
        call_stack.top();
    }
    else
    {
        cout << ' ';
    }
    cout << " ]";
    
    cout << endl;
}