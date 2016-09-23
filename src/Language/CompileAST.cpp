#include "CompileAST.hpp"
#include <iostream>
#include "Bytecode/InstructionSet.hpp"

using namespace Lang::Language::AST;


void CompileAST::operator()(const IntegerLiteral &integer_lit)
{
    std::cout << "(visit) IntegerLiteral visited: " << integer_lit.value << '\n';
    Bytecode::AST::InstructionCode push;
    push = Bytecode::AST::Unary { PUSH, integer_lit.value };
    environment.ast.emplace_back(push);
}

void CompileAST::operator()(const LongLiteral &long_lit)
{
    std::cout << "(visit) LongLiteral visited: " << long_lit.value << '\n';
}

void CompileAST::operator()(const FloatLiteral &float_lit)
{
    std::cout << "(visit) FloatLiteral visited: " << float_lit.value << '\n';
}

void CompileAST::operator()(const DoubleLiteral &double_lit)
{
    std::cout << "(visit) DoubleLiteral visited: " << double_lit.value << '\n';
}

void CompileAST::operator()(const StringLiteral &string_lit)
{
    std::cout << "(visit) StringLiteral visited: " << string_lit.value << '\n';
}

void CompileAST::operator()(const Literal& literal)
{
    boost::apply_visitor(*this, literal);
}

void CompileAST::operator()(const Variable& variable)
{
    std::cout << "[Variable] " << "name: " << variable.name << "type: ";
    std::cout << '\n';
}

void CompileAST::operator()(const Assignment &assignment)
{
    std::cout << "(visit) Assignment\n";
    boost::apply_visitor(*this, assignment.expression.get());
    // Added to byte code
    Bytecode::AST::InstructionCode store;
    store = Bytecode::AST::Unary { STORE, 0 };
    environment.ast.emplace_back(store);
}

void CompileAST::operator()(const Expression &expression)
{
    std::cout << "(visit) Expression\n";
    boost::apply_visitor(*this, expression);
}

void CompileAST::operator()(const Statement &statement)
{
    std::cout << "(visit) Statement\n";
    boost::apply_visitor(*this, statement);
}

void CompileAST::operator()(const Line& line)
{
    
}

void CompileAST::operator()(const Block& block)
{
    
}

void CompileAST::operator()(const Function& function)
{
    
}

void CompileAST::operator()(const Program& program)
{
    
}
