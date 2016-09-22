#include "Bytecode/InstructionSet.hpp"
#include "Language/Visitors.hpp"
#include <iostream>

using namespace Lang::Language::AST;


void ASTVisitor::operator()(const IntegerLiteral &integer_lit) const
{
    std::cout << "(visit) IntegerLiteral visited: " << integer_lit.value << '\n';
    Bytecode::AST::InstructionCode push;
    push = Bytecode::AST::Unary { PUSH, integer_lit.value };
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

void ASTVisitor::operator()(const Literal& literal) const
{
    boost::apply_visitor(*this, literal);
}

void ASTVisitor::operator()(const Variable& variable) const
{
    std::cout << "[Variable] " << "name: " << variable.name << "type: ";
    std::cout << '\n';
}

void ASTVisitor::operator()(const Assignment &assignment) const
{
    std::cout << "(visit) Assignment\n";
    boost::apply_visitor(*this, assignment.expression.get());
    // Added to byte code
    Bytecode::AST::InstructionCode store;
    store = Bytecode::AST::Unary { STORE, 0 };
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

void ASTVisitor::operator()(const Line& assignment) const
{
    
}

void ASTVisitor::operator()(const Block& assignment)
{
    
}

void ASTVisitor::operator()(const Function& assignment) const
{
    
}

void ASTVisitor::operator()(const Program& assignment) const
{
    
}


// PrintAST implementation

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
    ++indent_level;
    operator()(assignment.variable);
    boost::apply_visitor(*this, assignment.expression.get());
    --indent_level;
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

//void PrintAST::operator()(const Block& block)
//{
//    ++indent_level;
//    for (auto& line : block)
//    {
//        boost::apply_visitor(*this, line);
//    }
//}

void PrintAST::operator()(const Function& function)
{
    std::cout << "[Function] " << "name: " << function.name << " return type: ";
    print_type(function.return_type);
    std::cout << '\n';
    ++indent_level;
    for (auto& line : function.code)
    {
        boost::apply_visitor(*this, line);
    }
    --indent_level;
}

//void PrintAST::operator()(const Program& program)
//{
//    for (auto& function : program)
//    {
//        boost::apply_visitor(*this, function);
//    }
//}

void PrintAST::print_indents(int num_indents) const
{
    for (int i { 0 }; i < num_indents; ++i)
    {
        std::cout << "    ";
    }
}

void PrintAST::print_type(Type t) const
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
