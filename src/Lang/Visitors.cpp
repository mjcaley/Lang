#include "Lang/Visitors.hpp"
#include "StackMachine/VM.hpp"
#include "StackMachine/Visitors.hpp"
#include <iostream>

using namespace Lang::AST;
namespace sm_ast = StackMachine::AST;


void ASTVisitor::operator()(const Lang::AST::IntegerLiteral &integer_lit) const
{
    std::cout << "(visit) IntegerLiteral visited: " << integer_lit.value << '\n';
    sm_ast::InstructionCode push;
    push = sm_ast::Unary { StackMachine::InstructionSet::PUSH, integer_lit.value };
    environment.ast.emplace_back(push);
}

void ASTVisitor::operator()(const Lang::AST::LongLiteral &long_lit) const
{
    std::cout << "(visit) LongLiteral visited: " << long_lit.value << '\n';
}

void ASTVisitor::operator()(const Lang::AST::FloatLiteral &float_lit) const
{
    std::cout << "(visit) FloatLiteral visited: " << float_lit.value << '\n';
}

void ASTVisitor::operator()(const Lang::AST::DoubleLiteral &double_lit) const
{
    std::cout << "(visit) DoubleLiteral visited: " << double_lit.value << '\n';
}

void ASTVisitor::operator()(const Lang::AST::StringLiteral &string_lit) const
{
    std::cout << "(visit) StringLiteral visited: " << string_lit.value << '\n';
}

void ASTVisitor::operator()(const Lang::AST::Assignment &assignment) const
{
    std::cout << "(visit) Assignment\n";
    boost::apply_visitor(*this, assignment.expression.get());
    // Added to byte code
    sm_ast::InstructionCode store;
    store = sm_ast::Unary { StackMachine::InstructionSet::STORE, 0 };
    environment.ast.emplace_back(store);
}

void ASTVisitor::operator()(const Lang::AST::Expression &expression) const
{
    std::cout << "(visit) Expression\n";
    boost::apply_visitor(*this, expression);
}

void ASTVisitor::operator()(const Lang::AST::Statement &statement) const
{
    std::cout << "(visit) Statement\n";
    boost::apply_visitor(*this, statement);
}


bool Lang::stage1(const AST::Program& ast, AST::Environment& environment)
{
    for (auto& block : ast)
    {
        std::cout << "(visit) Block\n";
        boost::apply_visitor(ASTVisitor(environment), block);
        std::cout << "end of line" << std::endl;
    }
    
    return true;
}

bool Lang::stage2(const StackMachine::AST::Program& ast, StackMachine::StackMachineFile* smf)
{
    StackMachine::compile(ast, smf);
    return true;
}

std::unique_ptr<StackMachine::StackMachineFile> Lang::compile(const AST::Program& ast)
{
    auto environment = Environment();
    auto s1_result = stage1(ast, environment);
    
    auto smf = StackMachine::StackMachineFile::create();
    auto s2_result = stage2(environment.ast, smf.get());
    
    return std::move(smf);
}