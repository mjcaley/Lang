#include "VM.hpp"
#include <iomanip>
#include <iostream>
#include <boost/algorithm/string/join.hpp>

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
                data_stack.push_back(program[ip]);
                ++ip;
                
                if (debug)
                {
                    unaryDebugMessage(ip-2);
                }
                break;
            case POP:
                data_stack.pop_back();
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
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    data_stack.push_back( operand1 + operand2 );
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::subtract()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    data_stack.push_back( operand2 - operand1 );
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::multiply()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    data_stack.push_back(operand1 * operand2);
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::divide()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    data_stack.push_back( operand2 / operand1 );
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::modulus()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    data_stack.push_back( operand2 % operand1 );
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
    const auto test = data_stack.back();
    data_stack.pop_back();
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
    const auto test = data_stack.back();
    data_stack.pop_back();
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
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    
    if (operand1 == operand2)
    {
        data_stack.push_back(true);
    }
    else
    {
        data_stack.push_back(false);
    }
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::less_than()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    
    if (operand2 < operand1)
    {
        data_stack.push_back(true);
    }
    else
    {
        data_stack.push_back(false);
    }
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::greater_than()
{
    const auto operand1 = data_stack.back();
    data_stack.pop_back();
    const auto operand2 = data_stack.back();
    data_stack.pop_back();
    
    if (operand2 > operand1)
    {
        data_stack.push_back(true);
    }
    else
    {
        data_stack.push_back(false);
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
    data_stack.push_back(nargs);
    call_stack.push_back(++ip);
    ip = address;
    
    if(debug)
    {
        binaryDebugMessage(orig_ip);
    }
}

void VM::ret()
{
    auto orig_ip = ip;
    
    const auto ret_address = call_stack.back();
    call_stack.pop_back();
    ip = ret_address;
    
    if (debug)
    {
        nullaryDebugMessage(orig_ip);
    }
}

void VM::load()
{
    ++ip;   // Advance to data
    data_stack.push_back( memory[program[ip]] );
    ++ip;
    
    if (debug)
    {
        unaryDebugMessage(ip-2);
    }
}

void VM::store()
{
    ++ip;   // Advance to data
    const auto value = data_stack.back();
    memory[program[ip]] = value;
    data_stack.pop_back();
    ++ip;
    
    if (debug)
    {
        unaryDebugMessage(ip-2);
    }
}

void VM::print()
{
    const auto operand = data_stack.back();
    data_stack.pop_back();
    std::cout << operand << std::endl;
    ++ip;
    
    if (debug)
    {
        nullaryDebugMessage(ip-1);
    }
}

void VM::dup()
{
    data_stack.push_back(data_stack.back());
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
    using std::to_string;
    using boost::algorithm::join;
    
    
    std::string lcolumn, mcolumn, rcolumn;
    
    lcolumn = instruction_strings[*iter] + ' ';
    {
        iter++;
        std::vector<std::string> operands;
        for (; iter != end; ++iter)
        {
            operands.emplace_back(to_string(*iter));
        }
        lcolumn += join(operands, " ");
    }
    
    mcolumn = "Data stack: [ ";
    {
        std::vector<std::string> data_values;
        for (const auto& i : data_stack)
        {
            data_values.emplace_back(to_string(i));
        }
        mcolumn += join(data_values, ", ");
    }
    mcolumn += " ] ";
    
    
    rcolumn = "Call stack: ";
    {
        std::vector<std::string> call_values;
        for (const auto& i : call_stack)
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
}