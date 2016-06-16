#include <catch.hpp>

#include "Language/AST.hpp"
#include "Language/Grammar.hpp"
#include <string>
#include <boost/spirit/home/x3.hpp>


TEST_CASE( "Lang integer literal parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program = "1";
    auto iter = program.begin();
    auto end = program.end();
    
    AST::IntegerLiteral ast;
    auto& grammar = Grammar::int_lit;
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang long literal parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program = "6000000000";
    auto iter = program.begin();
    auto end = program.end();
    
    AST::LongLiteral ast;
    auto& grammar = Grammar::long_lit;
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang float literal parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program = "0.123";
    auto iter = program.begin();
    auto end = program.end();
    
    AST::FloatLiteral ast;
    auto& grammar = Grammar::float_lit;
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang double literal parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program = "0.123";
    auto iter = program.begin();
    auto end = program.end();
    
    AST::DoubleLiteral ast;
    auto& grammar = Grammar::double_lit;
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang string literal parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program = "\"This is a string\"";
    auto iter = program.begin();
    auto end = program.end();
    
    AST::StringLiteral ast;
    auto& grammar = Grammar::string_lit;
    bool result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang variable definition parsing", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Variable ast;
    auto& grammar = Grammar::variable;
    
    // integer
    program = "variable : int";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // long
    program = "variable : long";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // float
    program = "variable : float";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // double
    program = "variable : double";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // no spaces
    program = "variable:int";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // no type
    program = "variable";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang variable assignment", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Assignment ast;
    auto& grammar = Grammar::assignment;
    
    // with variable declaration
    program = "variable: int = 3";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
    
    // without variable declaration
    program = "variable = 3";
    iter = program.begin();
    end = program.end();
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
}