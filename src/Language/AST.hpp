#pragma once
#include <string>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace Lang { namespace Language { namespace AST {
    
    namespace x3 = boost::spirit::x3;
    using x3::int_;
    using x3::long_;
    using x3::float_;
    using x3::double_;
    
    struct IntegerLiteral
    {
        int value;
    };
    
    struct LongLiteral
    {
        long value;
    };
    
    struct FloatLiteral
    {
        float value;
    };
    
    struct DoubleLiteral
    {
        double value;
    };
    
    struct StringLiteral
    {
        std::string value;
    };
    
    enum class Operator
    {
        ASSIGN,
        EQUAL,
        NOT_EQUAL,
        LESS_THAN,
        GREATER_THAN,
        LESS_THAN_OR_EQUAL,
        GREATER_THAN_OR_EQUAL,
        END_OF_STATEMENT
    };
    
    enum class Type
    {
        UNDEFINED,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
        STRING,
        REFERENCE
    };
    
    struct Variable
    {
        std::string name;
        Type type { Type::UNDEFINED };
    };
    
    
    struct Expression;
    
    struct Assignment
    {
        Variable variable;
        x3::forward_ast<Expression> expression;
    };
    
    struct Statement : public x3::variant<Assignment>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct Expression : public x3::variant<IntegerLiteral, LongLiteral, FloatLiteral, DoubleLiteral, StringLiteral>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct Block : public x3::variant<Statement, Expression>
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Program = std::vector<Block>;
    
} } }



BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::Variable,
                          (std::string, name),
                          (Lang::Language::AST::Type, type)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::IntegerLiteral,
                          (int, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::LongLiteral,
                          (long, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::FloatLiteral,
                          (float, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::DoubleLiteral,
                          (double, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::StringLiteral,
                          (std::string, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::Language::AST::Assignment,
                          (Lang::Language::AST::Variable, variable),
                          (Lang::Language::AST::Expression, expression)
                          )