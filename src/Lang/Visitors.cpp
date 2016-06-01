#include "Lang/Visitors.hpp"
#include <iostream>

using namespace Lang::AST;


void ExpressionVisitor::operator()(const IntegerLiteral& integer_lit) const
{
    std::cout << "(visit) IntegerLiteral visited: " << integer_lit.value << '\n';
}

void ExpressionVisitor::operator()(const LongLiteral& long_lit) const
{
    std::cout << "(visit) LongLiteral visited: " << long_lit.value << '\n';
}

void ExpressionVisitor::operator()(const FloatLiteral& float_lit) const
{
    std::cout << "(visit) FloatLiteral visited: " << float_lit.value << '\n';
}

void ExpressionVisitor::operator()(const DoubleLiteral& double_lit) const
{
    std::cout << "(visit) DoubleLiteral visited: " << double_lit.value << '\n';
}

void ExpressionVisitor::operator()(const StringLiteral& string_lit) const
{
    std::cout << "(visit) StringLiteral visited: " << string_lit.value << '\n';
}

void StatementVisitor::operator()(const Assignment& assignment) const
{
    std::cout << "(visit) Assignment\n";
    boost::apply_visitor(ExpressionVisitor(ast), assignment.expression.get());
}

void BlockVisitor::operator()(const Expression& expression) const
{
    std::cout << "(visit) Expression\n";
    boost::apply_visitor(ExpressionVisitor(ast), expression);
}

void BlockVisitor::operator()(const Statement& statement) const
{
    std::cout << "(visit) Statement\n";
    boost::apply_visitor(StatementVisitor(ast), statement);
}

std::unique_ptr<StackMachine::StackMachineFile> Lang::AST::generate(Program& ast)
{
    StackMachine::AST::Program stackmachine_ast;
    
    for (auto& block : ast)
    {
        std::cout << "(visit) Block\n";
        boost::apply_visitor(BlockVisitor(stackmachine_ast), block);
    }
    
    auto smf = StackMachine::StackMachineFile::create();
    // stackmachine_ast to byte code
    
    return std::move(smf);
}
