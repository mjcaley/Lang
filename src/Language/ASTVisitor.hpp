#pragma once
#include <map>
#include <vector>
#include "Bytecode/AST.hpp"
#include "Language/AST.hpp"
#include "LangFile.hpp"
#include "Language/Environment.hpp"


namespace Lang { namespace Language { namespace AST {
    
    struct ASTVisitor : public boost::static_visitor<>
    {
        ASTVisitor(Lang::Language::Environment& environment) : environment(environment) {};
        
        virtual void operator()(const IntegerLiteral& integer_lit) = 0;
        virtual void operator()(const LongLiteral& long_lit) = 0;
        virtual void operator()(const FloatLiteral& float_lit) = 0;
        virtual void operator()(const DoubleLiteral& double_lit) = 0;
        virtual void operator()(const StringLiteral& string_lit) = 0;
        virtual void operator()(const Literal& literal) = 0;
        
        virtual void operator()(const Variable& variable) = 0;
        
        virtual void operator()(const Assignment& assignment) = 0;
        
        virtual void operator()(const Statement& statement) = 0;
        virtual void operator()(const Expression& expression) = 0;
        virtual void operator()(const Line& line) = 0;
        virtual void operator()(const Block& block) = 0;
        
        virtual void operator()(const Function& function) = 0;
        
        virtual void operator()(const Program& program) = 0;
        
    protected:
        Environment& environment;
    };
    
} } }
