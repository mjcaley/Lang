#include "Language/Visitors.hpp"
#include "VM/VM.hpp"
#include <iostream>

using namespace Lang::Language::AST;


void ASTVisitor::operator()(const IntegerLiteral &integer_lit) const
{
    std::cout << "(visit) IntegerLiteral visited: " << integer_lit.value << '\n';
    Bytecode::AST::InstructionCode push;
    push = Bytecode::AST::Unary { VM::InstructionSet::PUSH, integer_lit.value };
    environment.ast.emplace_back(push);
}

void ASTVisitor::operator()(const LongLiteral &long_lit) const
{
    std::cout << "(visit) LongLiteral visited: " << long_lit.value << '\n';
}

void ASTVisitor::operator()(const FloatLiteral &float_lit) const
{
    std::cout << "(visit) FloatLiteral visited: " << float_lit.value << '\n';
}

void ASTVisitor::operator()(const DoubleLiteral &double_lit) const
{
    std::cout << "(visit) DoubleLiteral visited: " << double_lit.value << '\n';
}

void ASTVisitor::operator()(const StringLiteral &string_lit) const
{
    std::cout << "(visit) StringLiteral visited: " << string_lit.value << '\n';
}

void ASTVisitor::operator()(const Assignment &assignment) const
{
    std::cout << "(visit) Assignment\n";
    boost::apply_visitor(*this, assignment.expression.get());
    // Added to byte code
    Bytecode::AST::InstructionCode store;
    store = Bytecode::AST::Unary { VM::InstructionSet::STORE, 0 };
    environment.ast.emplace_back(store);
}

void ASTVisitor::operator()(const Expression &expression) const
{
    std::cout << "(visit) Expression\n";
    boost::apply_visitor(*this, expression);
}

void ASTVisitor::operator()(const Statement &statement) const
{
    std::cout << "(visit) Statement\n";
    boost::apply_visitor(*this, statement);
}