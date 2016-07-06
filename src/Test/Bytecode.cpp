#include <catch.hpp>

#include "Bytecode/InstructionSet.hpp"
#include "Bytecode/AST.hpp"
#include "Bytecode/Grammar.hpp"
#include <string>
#include <boost/spirit/home/x3.hpp>


TEST_CASE( "Nullary parsing", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Nullary ast;
    auto& grammar = Grammar::nullary_op;
    
    // halt
    program = "halt";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // pop
    program = "pop";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // add
    program = "add";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // sub
    program = "sub";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // mul
    program = "mul";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // eq
    program = "eq";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // lt
    program = "lt";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // gt
    program = "gt";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // prnt
    program = "prnt";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // ret
    program = "ret";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // dup
    program = "dup";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
}

TEST_CASE( "Unary parsing", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Unary ast;
    auto& grammar = Grammar::unary_op;
    
    // push
    program = "push 1";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // load
    program = "load 2";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // store
    program = "store 3";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Label parsing", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program = "label:";
    auto iter = program.begin();
    auto end = program.end();
    AST::Label ast;
    auto& grammar = Grammar::label;
    
    bool result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Jump parsing", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Jump ast;
    auto& grammar = Grammar::jump_op;
    
    // jmp
    program = "jmp 1";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // jt
    program = "jt 2";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
    
    // jf
    program = "jf 3";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Call parsing", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program = "call 0";
    auto iter = program.begin();
    auto end = program.end();
    AST::Call ast;
    auto& grammar = Grammar::call_op;
    
    bool result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Implement recursive factorial", "[Bytecode]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Bytecode::AST;
    namespace Grammar = Lang::Bytecode::Grammar;
    
    std::string program =
    "               jmp main\n"
    "factorial:\n"
    "               load 0              ; 10\n"
    "               dup                 ; 10 10\n"
    "               push 1              ; 10 10 1\n"
    "               sub                 ; 10 9\n"
    "               dup                 ; 10 9 9\n"
    "               push 2              ; 10 9 9 2\n"
    "               lt                  ; 10 9 0\n"
    "               jt factorial_ret    ; 10 9\n"
    "               push 1              ; 10 9 1\n"
    "               call factorial\n"
    "factorial_ret:\n"
    "               mul\n"
    "               ret\n"
    
    "main:\n"
    "               push 10\n"
    "               push 1\n"
    "               call factorial\n"
    "               prnt\n"
    "               halt\n";
    
    auto iter = program.begin();
    auto end = program.end();
    AST::Program ast;
    auto& grammar = Grammar::program;
    
    bool result = x3::phrase_parse(iter, end, grammar, Grammar::skipper, ast);
    
    REQUIRE((result && iter == end) == true);
}