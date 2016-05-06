#include <iostream>
#include <tuple>
#include <boost/spirit/home/x3.hpp>
#include <boost/spirit/home/x3/support/ast/variant.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/std_pair.hpp>
#include <boost/fusion/include/io.hpp>


template<typename T>
std::pair<bool, std::string> program_test(T& parser, std::string test_name, std::string program)
{
    auto iter = program.begin();
    auto end = program.end();
    
    using boost::spirit::x3::phrase_parse;
    using boost::spirit::x3::ascii::space;
    bool result = phrase_parse(iter, end, parser, space);
    
    if (result)
    {
        return std::make_pair(true, test_name);
    }
    else
    {
        return std::make_pair(false, test_name);
    }
}

std::string bool_to_string(bool b)
{
    if (b)
    {
        return "true";
    }
    else{
        return "false";
    }
}

void print_test_result(std::pair<bool, std::string> result)
{
    std::cout << "Test " << result.second << ": " << bool_to_string(result.first) << std::endl;
}


namespace Lang { namespace runtime {
    std::map<std::string, long> integers;
    std::map<std::string, double> doubles;
} }


namespace Lang { namespace ast {
    namespace x3 = boost::spirit::x3;
    
    class Function;
    
    class LangObject
    {
    public:
        LangObject() {};
        virtual ~LangObject() {};
    protected:
        
        std::map<std::string, Function> functions;
    };
    
    struct FunctionParameter
    {
        std::string name;
        
    };
    class Function : public LangObject
    {
    public:
        Function(std::string return_type) : return_type(return_type) {};
        Function(std::vector<FunctionParameter> parameters, std::string return_type) {  };
    private:
        std::string return_type;
        std::vector<FunctionParameter> parameters;
    };
    
    class Integer : public LangObject
    {
    public:
        Integer(long i = 0) : value(i) {}
        
        long getValue() { return value; };
        
    private:
        long value { 0 };
    };
} }

namespace Lang { namespace parser {
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;
    
    using x3::lit;
    using x3::lexeme;
    
    using ascii::char_;
    using ascii::string;
    
    using x3::long_;
    using x3::double_;
    
    using x3::bool_;
    
    using x3::alpha;
    using x3::alnum;
    
    
    x3::rule<class identifier> identifier = "identifier";
    x3::rule<class dotted_identifier> dotted_identifier = "dotted_identifier";
    
    x3::rule<class boolean> boolean = "boolean";
    x3::rule<class number> number = "number";
    
    x3::rule<class assignment_operator> assignment_operator = "assignment_operator (=)";
    x3::rule<class add_operator> add_operator = "add_operator (+)";
    
    x3::rule<class statement> statement = "statement";
    x3::rule<class lang> lang = "lang";
    
    
    auto const identifier_def = ( alpha | '_' ) >> *( alnum );
    auto const dotted_identifier_def = identifier >> +( '.' >> identifier );
    
    auto const boolean_def = lit("true") | lit("false");
    auto const number_def = long_ | double_;
    
    auto const assignment_operator_def = ( identifier | dotted_identifier ) >> '=' >> ( statement ); // use expression after defining it
    auto const add_operator_def = number >> +( '+' >>  number );
    
    auto const statement_def = +( (add_operator | boolean) >> ';' );
    auto const lang_def = statement;
    
    BOOST_SPIRIT_DEFINE (
                         identifier,
                         dotted_identifier,
                         boolean,
                         number,
                         add_operator,
                         statement,
                         lang
                        )
} }

namespace Test
{
    namespace x3 = boost::spirit::x3;
    namespace ascii = boost::spirit::x3::ascii;
    
    auto const print = [](auto& ctx){std::cout<<"Value: "<<x3::_attr(ctx)<<std::endl;};
    
    x3::rule<class test> test = "test";
    auto const test_def = (x3::double_|x3::long_ )[print];
    BOOST_SPIRIT_DEFINE(test);
}


void implementation()
{
    std::pair<bool, std::string> test_result;
    auto parser = Lang::parser::lang;
    print_test_result(program_test(parser, "int_add", "2 + 3;"));
    print_test_result(program_test(parser, "int_multi_add", "2 + 3 + 4+5;"));
    print_test_result(program_test(parser, "bool_true", "true;"));
    print_test_result(program_test(parser, "bool_false", "false;"));
    print_test_result(program_test(parser, "double_add", "4.2 + 1.0 + 4.2;"));
    print_test_result(program_test(parser, "semicolon_error", "4+5"));
}

void test()
{
    std::pair<bool, std::string> test_result;
    auto parser = Test::test;
    print_test_result(program_test(parser, "test", "3"));
}

int main()
{
    std::cout << "Lang\n" << std::endl;
    
    //implementation();
    test();
    
    return 0;
}