#pragma once
#include "Language/ASTVisitor.hpp"


namespace Lang { namespace Language { namespace AST {

    struct PrintAST : public ASTVisitor
    {
        void operator()(const IntegerLiteral& integer_lit) override;
        void operator()(const LongLiteral& long_lit) override;
        void operator()(const FloatLiteral& float_lit) override;
        void operator()(const DoubleLiteral& double_lit) override;
        void operator()(const StringLiteral& string_lit) override;
        void operator()(const Literal& literal) override;
        
        void operator()(const Variable& variable) override;
        
        void operator()(const Assignment& assignment) override;
        
        void operator()(const Statement& assignment) override;
        void operator()(const Expression& assignment) override;
        void operator()(const Line& assignment) override;
        void operator()(const Block& assignment) override;
        
        void operator()(const Function& assignment) override;
        
        void operator()(const Program& assignment) override;
        
    private:
        int indent_level { 0 };
        
        void increase_indent() { ++indent_level; };
        void decrease_indent() { --indent_level; };
        void print_indents(int num_indents);
        void print_type(Type t);
    };
    
} } }
