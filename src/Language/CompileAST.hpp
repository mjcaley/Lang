#pragma once
#include "Language/ASTVisitor.hpp"


namespace Lang { namespace Language { namespace AST {

    struct CompileAST : public ASTVisitor
    {
        CompileAST(Lang::Language::Environment& environment) : ASTVisitor(environment) {}
        
        void operator()(const IntegerLiteral& integer_lit) override;
        void operator()(const LongLiteral& long_lit) override;
        void operator()(const FloatLiteral& float_lit) override;
        void operator()(const DoubleLiteral& double_lit) override;
        void operator()(const StringLiteral& string_lit) override;
        void operator()(const Literal& literal) override;
        
        void operator()(const Variable& variable) override;
        
        void operator()(const Assignment& assignment) override;
        
        void operator()(const Statement& statement) override;
        void operator()(const Expression& expression) override;
        void operator()(const Line& line) override;
        void operator()(const Block& block) override;
        
        void operator()(const Function& function) override;
        
        void operator()(const Program& program) override;
    };

} } }
