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
        
        void operator()(const IntegerLiteral& integer_lit) const;
        void operator()(const LongLiteral& long_lit) const;
        void operator()(const FloatLiteral& float_lit) const;
        void operator()(const DoubleLiteral& double_lit) const;
        void operator()(const StringLiteral& string_lit) const;
        
        void operator()(const Assignment& assignment) const;
        
        void operator()(const Expression& assignment) const;
        void operator()(const Statement& assignment) const;
        
    private:
        Environment& environment;
    };
    
} } }