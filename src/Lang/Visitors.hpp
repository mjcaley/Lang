#pragma once
#include <map>
#include <vector>
#include "Lang/AST.hpp"
#include "StackMachine/AST.hpp"
#include "StackMachine/StackMachineFile.hpp"


namespace Lang { namespace AST {
    using std::map;
    using std::shared_ptr;
    using std::unique_ptr;
    using std::vector;
    using StackMachine::StackMachineFile;
    
    struct Scope
    {
        StackMachine::AST::Program scoped_ast {};
        map<std::string, std::pair<int, Type>> variables;
    };
    
    struct Environment
    {
        vector<Scope> scopes { Scope() };
        StackMachine::AST::Program ast;
    };
    
    
    struct ASTVisitor : public boost::static_visitor<>
    {
        ASTVisitor(Environment& environment) : environment(environment) {};
        
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
    
} }

namespace Lang
{
    bool stage1(const Lang::AST::Program& ast, Lang::AST::Environment& environment);
    bool stage2(const StackMachine::AST::Program& ast, StackMachine::StackMachineFile* smf);
    std::unique_ptr<StackMachine::StackMachineFile> compile(const Lang::AST::Program& ast);
}