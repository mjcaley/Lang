#include "Bytecode/Visitors.hpp"

using namespace Lang::Bytecode::AST;


void CodeGenerator::operator()(const Jump& jump) const
{
    byte_code.emplace_back(jump.instruction);
    JumpArgGen arg_generator(byte_code, label_map);
    boost::apply_visitor(arg_generator, jump.position);
}

void CodeGenerator::operator()(const Call& call) const
{
    byte_code.emplace_back(call.instruction);
    JumpArgGen arg_generator(byte_code, label_map);
    boost::apply_visitor(arg_generator, call.position);
}

void CodeGenerator::operator()(const Unary& unary_op) const
{
    byte_code.emplace_back(unary_op.instruction);
    byte_code.emplace_back(unary_op.operand);
}

void CodeGenerator::operator()(const Nullary& nullary_op) const
{
    byte_code.emplace_back(nullary_op.instruction);
}

void CodeGenerator::operator()(const Binary& binary_op) const
{
    byte_code.emplace_back(binary_op.instruction);
    byte_code.emplace_back(binary_op.operand1);
    byte_code.emplace_back(binary_op.operand2);
}