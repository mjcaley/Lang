#pragma once
#include <iostream>
#include <map>
#include "Language/Visitors.hpp"
#include "Language/AST.hpp"
#include "LangFile.hpp"
#include "Bytecode/Functions.hpp"
#include "Language/Environment.hpp"
#include "Language/Scope.hpp"


namespace Lang { namespace Language {
    
    using Lang::LangFile;
    using std::map;
    
    bool stage1(const AST::Program& ast, Environment& environment)
    {
        AST::PrintAST visitor(environment);
        for (auto& function : ast)
        {
            //std::cout << "(visit) Block\n";
            //boost::apply_visitor(AST::ASTVisitor(environment), block);
            //std::cout << "end of line" << std::endl;
            
            visitor(function);
        }
        
        return true;
    }
    
    bool stage2(const Bytecode::AST::Program& ast, LangFile& file)
    {
        Bytecode::compile(ast, file);
        return true;
    }
    
    std::unique_ptr<LangFile> compile(const AST::Program& ast)
    {
        auto environment = Environment();
        auto s1_result = stage1(ast, environment);
        
        auto file = LangFile::create();
        //auto s2_result = stage2(environment.ast, *file);
        
        return std::move(file);
    }
    
} }
