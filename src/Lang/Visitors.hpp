#pragma once
#include <vector>
#include "Lang/AST.hpp"
#include "StackMachine/AST.hpp"
#include "StackMachine/StackMachineFile.hpp"


namespace Lang { namespace AST {
    using StackMachine::StackMachineFile;
    
    struct ExpressionVisitor : public boost::static_visitor<>
    {
        ExpressionVisitor(StackMachine::AST::Program& ast) : ast(ast) {}
        
        void operator()(const IntegerLiteral& integer_lit) const;
        void operator()(const LongLiteral& long_lit) const;
        void operator()(const FloatLiteral& float_lit) const;
        void operator()(const DoubleLiteral& double_lit) const;
        void operator()(const StringLiteral& string_lit) const;
        
    private:
        StackMachine::AST::Program& ast;
    };
    
    struct StatementVisitor : public boost::static_visitor<>
    {
        StatementVisitor(StackMachine::AST::Program& ast) : ast(ast) {}
        
        void operator()(const Assignment& assignment) const;
        
    private:
        StackMachine::AST::Program& ast;
    };
    
    struct BlockVisitor : public boost::static_visitor<>
    {
        BlockVisitor(StackMachine::AST::Program& ast) : ast(ast) {}
        
        void operator()(const Expression& assignment) const;
        void operator()(const Statement& assignment) const;
        
    private:
        StackMachine::AST::Program& ast;
    };
    
    std::unique_ptr<StackMachineFile> generate(Program& ast);
    
} }