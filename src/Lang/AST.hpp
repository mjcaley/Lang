#pragma once
#include <string>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>


namespace Lang { namespace AST {
    
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
    
    struct Literal : public x3::variant< IntegerLiteral, LongLiteral, FloatLiteral, DoubleLiteral, StringLiteral >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct LHS : public x3::variant< Variable >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    struct RHS : public x3::variant< Literal >
    {
        using base_type::base_type;
        using base_type::operator=;
    };
    
    using Token = x3::variant< LHS, RHS >;

    using Program = std::vector<Token>;
    
} }



BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::Variable,
                          (std::string, name),
                          (Lang::AST::Type, type)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::IntegerLiteral,
                          (int, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::LongLiteral,
                          (long, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::FloatLiteral,
                          (float, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::DoubleLiteral,
                          (double, value)
                          );

BOOST_FUSION_ADAPT_STRUCT(
                          Lang::AST::StringLiteral,
                          (std::string, value)
                          );