#include "PrintAST.hpp"
#include <iostream>

using namespace Lang::Language::AST;


void PrintAST::operator()(const IntegerLiteral& integer_lit)
{
    print_indents(indent_level);
    std::cout << "[IntegerLiteral] " << integer_lit.value << '\n';
}

void PrintAST::operator()(const LongLiteral& long_lit)
{
    print_indents(indent_level);
    std::cout << "[LongLiteral] " << long_lit.value << '\n';
}

void PrintAST::operator()(const FloatLiteral& float_lit)
{
    print_indents(indent_level);
    std::cout << "[FloatLiteral] " << float_lit.value << '\n';
}

void PrintAST::operator()(const DoubleLiteral& double_lit)
{
    print_indents(indent_level);
    std::cout << "[DoubleLiteral] " << double_lit.value << '\n';
}

void PrintAST::operator()(const StringLiteral& string_lit)
{
    print_indents(indent_level);
    std::cout << "[StringLiteral] " << string_lit.value << '\n';
}

void PrintAST::operator()(const Literal& literal)
{
    boost::apply_visitor(*this, literal);
}

void PrintAST::operator()(const Variable& variable)
{
    print_indents(indent_level);
    std::cout << "[Variable] " << "name: " << variable.name << " type: ";
    print_type(variable.type);
    std::cout << '\n';
}

void PrintAST::operator()(const Assignment& assignment)
{
    print_indents(indent_level);
    std::cout << "[Assignment] " << '\n';
    increase_indent();
    (*this)(assignment.variable);
    boost::apply_visitor(*this, assignment.expression.get());
    decrease_indent();
}


void PrintAST::operator()(const Statement& statement)
{
    boost::apply_visitor(*this, statement);
}

void PrintAST::operator()(const Expression& expression)
{
    boost::apply_visitor(*this, expression);
}

void PrintAST::operator()(const Line& line)
{
    boost::apply_visitor(*this, line);
}

void PrintAST::operator()(const Block& block)
{
    increase_indent();
    for (auto& line : block)
    {
        boost::apply_visitor(*this, line);
    }
    decrease_indent();
}

void PrintAST::operator()(const Function& function)
{
    std::cout << "[Function] " << "name: " << function.name << " return type: ";
    print_type(function.return_type);
    std::cout << '\n';
    for (auto& line : function.code)
    {
        (*this)(line);
    }
}

void PrintAST::operator()(const Program& program)
{
    for (auto& function : program)
    {
        (*this)(function);
    }
}

void PrintAST::print_indents(int num_indents)
{
    for (int i { 0 }; i < num_indents; ++i)
    {
        std::cout << "    ";
    }
}

void PrintAST::print_type(Type t)
{
    std::string type;
    if (t == Type::UNDEFINED)
    {
        type = "undefined";
    }
    else if (t == Type::INT)
    {
        type = "int";
    }
    else if (t == Type::LONG)
    {
        type = "long";
    }
    else if (t == Type::FLOAT)
    {
        type = "float";
    }
    else if (t == Type::DOUBLE)
    {
        type = "double";
    }
    else if (t == Type::STRING)
    {
        type = "string";
    }
    else if (t == Type::REFERENCE)
    {
        type = "reference";
    }
    
    std::cout << type;
}
