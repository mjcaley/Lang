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
        
        virtual void operator()(const IntegerLiteral& integer_lit) const;
        virtual void operator()(const LongLiteral& long_lit) const;
        virtual void operator()(const FloatLiteral& float_lit) const;
        virtual void operator()(const DoubleLiteral& double_lit) const;
        virtual void operator()(const StringLiteral& string_lit) const;
        virtual void operator()(const Literal& literal) const;
        
        virtual void operator()(const Variable& variable) const;
        
        virtual void operator()(const Assignment& assignment) const;
        
        virtual void operator()(const Statement& assignment) const;
        virtual void operator()(const Expression& assignment) const;
        virtual void operator()(const Line& assignment) const;
        virtual void operator()(const Block& assignment);
        
        virtual void operator()(const Function& assignment) const;
        
        virtual void operator()(const Program& assignment) const;
        
    protected:
        Environment& environment;
    };
    
    struct PrintAST : public boost::static_visitor<>
    {
        PrintAST(Lang::Language::Environment& environment) : environment(environment) {};
        
        void operator()(const IntegerLiteral& integer_lit);
        void operator()(const LongLiteral& long_lit);
        void operator()(const FloatLiteral& float_lit);
        void operator()(const DoubleLiteral& double_lit);
        void operator()(const StringLiteral& string_lit);
        void operator()(const Literal& literal);
        
        void operator()(const Variable& variable);
        
        void operator()(const Assignment& assignment);
        
        void operator()(const Statement& assignment);
        void operator()(const Expression& assignment);
        void operator()(const Line& assignment);
        //void operator()(const Block& assignment);
        
        void operator()(const Function& assignment);
        
        //void operator()(const Program& assignment);
    
    protected:
        Environment& environment;
    
    private:
        int indent_level { 0 };
        
        void print_indents(int num_indents) const;
        void print_type(Type t) const;
    };
    
} } }
