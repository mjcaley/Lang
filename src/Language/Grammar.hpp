#pragma once
#include "Language/AST.hpp"


namespace Lang { namespace Language { namespace Grammar {
    
    namespace x3 = boost::spirit::x3;
    namespace AST = Lang::Language::AST;
    
    using x3::alpha;
    using x3::alnum;
    using x3::char_;
    using x3::eol;
    using x3::int_;
    using x3::long_;
    using x3::float_;
    using x3::double_;
    using x3::lexeme;
    using x3::lit;
    using x3::no_skip;
    using x3::space;
    using x3::symbols;
    
    x3::symbols<AST::Type> types
    {
        { "int", AST::Type::INT },          { "long", AST::Type::LONG },
        { "double", AST::Type::DOUBLE },    { "float", AST::Type::FLOAT },
        { "string", AST::Type::STRING }
    };
    
    x3::symbols<AST::Operator> operators
    {
        { "=", AST::Operator::ASSIGN }
    };
    
    x3::rule<class identifier, std::string> const identifier("identifier");
    
    x3::rule<class int_lit, AST::IntegerLiteral> const int_lit("int_lit");
    x3::rule<class long_lit, AST::LongLiteral> const long_lit("long_lit");
    x3::rule<class float_lit, AST::FloatLiteral> const float_lit("float_lit");
    x3::rule<class double_lit, AST::DoubleLiteral> const double_lit("double_lit");
    x3::rule<class string_lit, AST::StringLiteral> const string_lit("string_lit");
    x3::rule<class literal, AST::Literal> const literal("literal");
    
    x3::rule<class variable, AST::Variable> const variable("variable declaration");
    
    x3::rule<class assignment, AST::Assignment> const assignment("assignment");
    
    x3::rule<class statement, AST::Statement> const statement("statement");
    x3::rule<class expression, AST::Expression> const expression("expression");
    x3::rule<class line, AST::Line> const line("line");
    x3::rule<class block, AST::Block> const block("block");
    
    x3::rule<class function, AST::Function> const function("function");
    
    x3::rule<class program, AST::Program> const program("program");
    
    
    auto const identifier_def = lexeme[(char_('_') | alpha) >> *( alnum | char_('_') )];
    
    auto const int_lit_def = int_;
    auto const long_lit_def = long_;
    auto const float_lit_def = float_ >> lit('f');
    auto const double_lit_def = double_ >> lit('d');
    auto const string_lit_def = '"' >> no_skip[*(char_ - '"' )] >> '"';
    auto const literal_def = float_lit | double_lit | int_lit | long_lit | string_lit;
    
    auto const variable_def = identifier >> -( ':' >> types );
    
    auto const assignment_def = variable >> '=' >> expression;
    
    auto const statement_def = assignment;
    auto const expression_def = literal;
    auto const line_def = ( statement | expression ) >> ';';
    auto const block_def = +line;
    
    auto const function_def = types >> identifier >> '(' >> /* *(types >> identifier >> *(',') ) */ ')' >> '{' >> -block >> '}';
    
    auto const program_def = +function;
    
    
    BOOST_SPIRIT_DEFINE(identifier);
    BOOST_SPIRIT_DEFINE(int_lit);
    BOOST_SPIRIT_DEFINE(long_lit);
    BOOST_SPIRIT_DEFINE(float_lit);
    BOOST_SPIRIT_DEFINE(double_lit);
    BOOST_SPIRIT_DEFINE(string_lit);
    BOOST_SPIRIT_DEFINE(literal);
    
    BOOST_SPIRIT_DEFINE(variable);
    
    BOOST_SPIRIT_DEFINE(assignment);
    
    BOOST_SPIRIT_DEFINE(statement);
    BOOST_SPIRIT_DEFINE(expression);
    BOOST_SPIRIT_DEFINE(line);
    BOOST_SPIRIT_DEFINE(block);
    
    BOOST_SPIRIT_DEFINE(function);
    
    BOOST_SPIRIT_DEFINE(program);
    
} } }
