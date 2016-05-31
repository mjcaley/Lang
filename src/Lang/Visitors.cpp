#include "Lang/Visitors.hpp"
#include <iostream>

using namespace Lang::AST;


void LiteralVisitor::operator()(const IntegerLiteral& integer_lit) const
{
    std::cout << "IntegerLiteral visited: " << integer_lit.value << std::endl;
}

void LiteralVisitor::operator()(const LongLiteral& long_lit) const
{
    std::cout << "LongLiteral visited: " << long_lit.value << std::endl;
}

void LiteralVisitor::operator()(const FloatLiteral& float_lit) const
{
    std::cout << "FloatLiteral visited: " << float_lit.value << std::endl;
}

void LiteralVisitor::operator()(const DoubleLiteral& double_lit) const
{
    std::cout << "DoubleLiteral visited: " << double_lit.value << std::endl;
}

void LiteralVisitor::operator()(const StringLiteral& string_lit) const
{
    std::cout << "StringLiteral visited: " << string_lit.value << std::endl;
}

void LHSVisitor::operator()(const Variable& var) const
{
    std::cout << "Variable visited" << std::endl;
}

void RHSVisitor::operator()(const Literal& lit) const
{
    std::cout << "Literal visited" << std::endl;
    boost::apply_visitor(LiteralVisitor(byte_code), lit);
}

void TokenVisitor::operator()(const LHS& lhs) const
{
    std::cout << "LHS visited" <<std::endl;
    boost::apply_visitor(LHSVisitor(byte_code), lhs);
}

void TokenVisitor::operator()(const RHS& rhs) const
{
    std::cout << "RHS visited" << std::endl;
    boost::apply_visitor(RHSVisitor(byte_code), rhs);
}

std::unique_ptr<StackMachine::StackMachineFile> Lang::AST::generate(Program& ast)
{
    auto smf = StackMachine::StackMachineFile::create();
    
    for (auto& token : ast)
    {
        boost::apply_visitor(TokenVisitor(smf->byte_code), token);
    }
    
    return std::move(smf);
}
