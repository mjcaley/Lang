#include "VM/VM.hpp"

using Lang::LangFile;
using namespace Lang::VM;


void VM::init()
{
    data.clear();
    call.clear();
    frame.clear();
    frame.push();
}

void VM::loadProgram(std::unique_ptr<LangFile> program)
{
    if (program)
    {
        this->program = std::move(program);
    }
}

bool VM::run()
{
    if (!program)
    {
        return false;
    }
    
    running = true;
    while(running && ip < program->length())
    {
        switch(program->byte_code[ip])
        {
            case HALT:
                running = false;
                
                if (debug)
                {
                    nullary_debug_message(ip);
                }
                break;
            case PUSH:
                ++ip;   // Advance to data
                data.push(program->byte_code[ip]);
                ++ip;
                
                if (debug)
                {
                    unary_debug_message(ip-2);
                }
                break;
            case POP:
                data.pop();
                ++ip;
                
                if (debug)
                {
                    nullary_debug_message(ip-1);
                }
                break;
            case ADD:
                add_op();
                break;
            case SUB:
                subtract_op();
                break;
            case MUL:
                multiply_op();
                break;
            case DIV:
                divide_op();
                break;
            case MOD:
                modulus_op();
                break;
            case JMP:
                jump_op();
                break;
            case JT:
                jump_if_true_op();
                break;
            case JF:
                jump_if_false_op();
                break;
            case EQ:
                equal_op();
                break;
            case LT:
                less_than_op();
                break;
            case GT:
                greater_than_op();
                break;
            case LOAD:
                load_op();
                break;
            case STORE:
                store_op();
                break;
            case PRNT:
                print_op();
                break;
            case CALL:
                call_op();
                break;
            case RET:
                ret_op();
                break;
            case DUP:
                dup_op();
                break;
            default:
                running = false;
                break;
        }
    }
    
    init();
    return true;
}

void VM::add_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    data.push( operand1 + operand2 );
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::subtract_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    data.push( operand2 - operand1 );
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::multiply_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    data.push(operand1 * operand2);
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::divide_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    data.push( operand2 / operand1 );
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::modulus_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    data.push( operand2 % operand1 );
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::jump_op()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to data
    ip = program->byte_code[ip];
    
    if (debug)
    {
        unary_debug_message(orig_ip);
    }
}

void VM::jump_if_true_op()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to data
    const auto test = data.tos();
    data.pop();
    if (test == true)
    {
        ip = program->byte_code[ip];
    }
    else
    {
        ++ip;
    }
    
    if (debug)
    {
        unary_debug_message(orig_ip);
    }
}

void VM::jump_if_false_op()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to data
    const auto test = data.tos();
    data.pop();
    if (test == false)
    {
        ip = program->byte_code[ip];
    }
    else
    {
        ++ip;
    }
    
    if (debug)
    {
        unary_debug_message(orig_ip);
    }
}

void VM::equal_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    
    if (operand1 == operand2)
    {
        data.push(true);
    }
    else
    {
        data.push(false);
    }
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::less_than_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    
    if (operand2 < operand1)
    {
        data.push(true);
    }
    else
    {
        data.push(false);
    }
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::greater_than_op()
{
    const auto operand1 = data.tos();
    data.pop();
    const auto operand2 = data.tos();
    data.pop();
    
    if (operand2 > operand1)
    {
        data.push(true);
    }
    else
    {
        data.push(false);
    }
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::call_op()
{
    auto orig_ip = ip;
    
    ++ip;   // Advance to call address
    const auto address = program->byte_code[ip];
    const auto nargs = data.tos();
    data.pop();
    
    frame.push();
    {
        auto i { 0 };
        auto riter = data.rbegin();
        const auto end = data.rbegin() + nargs;
        auto& cur_frame = frame.tos();
        for (; riter != end; ++i, ++riter)
        {
            cur_frame[i] = *riter;
            data.pop();
        }
    }

    call.push(++ip);
    ip = address;
    
    if(debug)
    {
        unary_debug_message(orig_ip);
    }
}

void VM::ret_op()
{
    auto orig_ip = ip;
    
    const auto ret_address = call.tos();
    call.pop();
    ip = ret_address;
    
    frame.pop();
    
    if (debug)
    {
        nullary_debug_message(orig_ip);
    }
}

void VM::load_op()
{
    ++ip;   // Advance to data
    auto& local = frame.tos();
    data.push( local[program->byte_code[ip]] );
    ++ip;
    
    if (debug)
    {
        unary_debug_message(ip-2);
    }
}

void VM::store_op()
{
    ++ip;   // Advance to data
    const auto value = data.tos();
    auto& local = frame.tos();
    local[program->byte_code[ip]] = value;
    data.pop();
    ++ip;
    
    if (debug)
    {
        unary_debug_message(ip-2);
    }
}

void VM::print_op()
{
    const auto operand = data.tos();
    data.pop();
    std::cout << operand << std::endl;
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::dup_op()
{
    data.push(data.tos());
    ++ip;
    
    if (debug)
    {
        nullary_debug_message(ip-1);
    }
}

void VM::nullary_debug_message(int ip)
{
    const auto begin = program->byte_code.begin() + ip;
    const auto end = program->byte_code.begin() + (ip + 1);
    debug_message(begin, end);
}

void VM::unary_debug_message(int ip)
{
    const auto begin = program->byte_code.begin() + ip;
    const auto end = program->byte_code.begin() + (ip + 2);
    debug_message(begin, end);
}