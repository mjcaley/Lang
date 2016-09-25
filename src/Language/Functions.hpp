#pragma once
#include <iostream>
#include <map>
#include "Language/CompileAST.hpp"
#include "Language/PrintAST.hpp"
#include "Language/AST.hpp"
#include "LangFile.hpp"
#include "Bytecode/Functions.hpp"
#include "Language/Environment.hpp"
#include "Language/Scope.hpp"


namespace Lang { namespace Language {
    
    using Lang::LangFile;
    using std::map;
    
    void print(const AST::Program& ast)
    {
        AST::PrintAST visitor;
        visitor(ast);
    }
    
    bool stage1(const AST::Program& ast, Environment& environment)
    {
        AST::CompileAST visitor(environment);
        visitor(ast);
        
        return true;
    }
    
    bool stage2(const Bytecode::AST::Program& ast, LangFile& file)
    {
        Bytecode::compile(ast, file);
        return true;
    }
    
    std::unique_ptr<LangFile> compile(const AST::Program& ast, bool print_ast)
    {
        Environment environment;
        auto s1_result = stage1(ast, environment);
        if (print_ast)
        {
            std::cout << "--------\n";
            std::cout << "Stage 1:\n";
            print(ast);
        }
        
        auto file = LangFile::create();
        auto s2_result = stage2(environment.ast, *file);
        if (print_ast)
        {
            std::cout << "--------\n";
            std::cout << "Stage 2:\n";
            print(ast);
        }
        
        return file;
    }
    
} }
