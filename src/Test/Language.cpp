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
    
    std::string program = "0.123f";
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
    
    std::string program = "0.123d";
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
    
    SECTION( "Declare integer" )
    {
        program = "variable : int";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Declare long" )
    {
        program = "variable : long";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Declare float" )
    {
        program = "variable : float";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Declare double" )
    {
        program = "variable : double";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Declare integer with no spaces" )
    {
        program = "variable:int";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Variable with no type" )
    {
        program = "variable";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
}

TEST_CASE( "Literal value", "[Language]" )
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    AST::Literal ast;
    auto& grammar = Grammar::assignment;
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
    
    SECTION( "No type declaration" )
    {
        AST::Assignment ast;
        program = "variable = 3";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Assigning integer" )
    {
        AST::Assignment ast;
        program = "variable: int = 3";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Assigning long" )
    {
        AST::Assignment ast;
        program = "variable: long = 3";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Assigning float" )
    {
        AST::Assignment ast;
        program = "variable: float = 4.2f";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Assigning double" )
    {
        AST::Assignment ast;
        program = "variable: double = 4.2d";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Assigning string" )
    {
        AST::Assignment ast;
        program = "variable: string = \"Hello world!\"";
        iter = program.begin();
        end = program.end();
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
}

TEST_CASE( "Lang block of code" , "[Language]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    auto& grammar = Grammar::block;

    program = "variable: int = 4;"
              "variable2: int = 2;";
    iter = program.begin();
    end = program.end();
    AST::Block ast;
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
}

TEST_CASE( "Lang function definition", "[Language]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    auto& grammar = Grammar::function;
    
    SECTION( "Empty function" )
    {
        program = "int main() {}";
        iter = program.begin();
        end = program.end();
        AST::Function ast;
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Empty function on multiple lines" )
    {
        program = "float main()\n"
        "{\n"
        "}\n";
        iter = program.begin();
        end = program.end();
        AST::Function ast;
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
    
    SECTION( "Function with multiple code lines" )
    {
        program = "int main()\n"
        "{\n"
        "    variable: int = 3;\n"
        "    variable2: int = 4;\n"
        //"    variable2: float = 4.0;\n"
        //"    variable_number_3: string = \"some words\";\n"
        "}";
        iter = program.begin();
        end = program.end();
        AST::Function ast;
        result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
        REQUIRE((result && iter == end) == true);
    }
}

TEST_CASE( "Lang program", "[Language]")
{
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    namespace Grammar = Lang::Language::Grammar;
    
    std::string program;
    std::string::const_iterator iter, end;
    bool result { false };
    auto& grammar = Grammar::program;
    
    program = "int add()\n"
    "{\n"
    "    anothervariable: int = 42;\n"
    "}\n"
    ""
    "int main()\n"
    "{\n"
    "    variable: int = 3;\n"
    //"    variable2: float = 4.0;\n"
    "    variable3: string = \"some words\";\n"
    "}";
    iter = program.begin();
    end = program.end();
    AST::Program ast;
    result = x3::phrase_parse(iter, end, grammar, x3::space, ast);
    REQUIRE((result && iter == end) == true);
}
