#pragma once
#include <ostream>
#include <string>
#include <boost/optional.hpp>
#include <boost/variant.hpp>


namespace Lang
{
    template<typename T>
    struct Reference
    {
        Reference() {};
        template<typename Arg>
        Reference(Arg arg) { data.set(arg); };
        
        unsigned getRefs() const { return refs; };
        unsigned incrementRef() { return ++refs; };
        unsigned decrementRef() { return --refs; };
        
        
        
        T data;
        
    private:
        unsigned refs { 0 };
    };
    
    enum class LangType
    {
        INTEGER,    INT = INTEGER,
        DOUBLE,     DBL = DOUBLE,
        STRING,     STR = STRING,
        FUNCTION,   FUNC = FUNCTION,
        STRUCT,
        TRAIT
    };
    
    template <typename T>
    struct Type
    {
        virtual ~Type() = default;
        
        virtual T& get() = 0;
        virtual void set(T) = 0;
        virtual LangType getType() const = 0;
        virtual std::string toString() const = 0;
        
        // Getter/setter shortcut
        virtual T operator()() { return get(); };
        virtual void operator()(T v) { set(v); };
        
        virtual bool operator==(const T& obj) { return get() == obj; };
        virtual bool operator!=(const T& obj) { return get() != obj; };
        virtual bool operator< (const T& obj) { return get() <  obj; };
        virtual bool operator> (const T& obj) { return get() >  obj; };
        virtual bool operator<=(const T& obj) { return get() <= obj; };
        virtual bool operator>=(const T& obj) { return get() >= obj; };
        
        template<typename S>
        friend std::ostream& operator<<(std::ostream& os, const S& obj)
        {
            os << obj.toString();
            return os;
        };
    };
    
    struct Integer : public Type<long>
    {
        Integer() = default;
        Integer(int i) { value = i; };
        ~Integer() { std::cout << "Integer dtor" << std::endl; };
        
        long& get() override { return value; };
        void set(long i) override { value = i; };
        LangType getType() const override { return LangType::INTEGER; };
        std::string toString() const override { return std::to_string(value); };
        
        long& operator++() { return ++value; };
        long& operator--() { return --value; };
        long operator++(int) { return value++; };
        long operator--(int) { return value--; };
        template<typename T>
        long operator+(const T& obj) { return value + obj; };
        template<typename T>
        long operator-(const T& obj) { return value - obj; };
        template<typename T>
        long operator*(const T& obj) { return value * obj; };
        template<typename T>
        long operator/(const T& obj) { return value / obj; };
        template<typename T>
        long operator%(const T& obj) { return value % obj; };
        
    private:
        long value { 0 };
    };
    using spInteger = std::shared_ptr<Integer>;
    
    struct Double : public Type<double>
    {
        Double() = default;
        Double(double d) { value = d; };
        
        double& get() override { return value; };
        void set(double d) override { value = d; };
        LangType getType() const override { return LangType::DOUBLE; };
        std::string toString() const override { return std::to_string(value); };
        
        double& operator++() { return ++value; };
        double& operator--() { return --value; };
        double operator++(int) { return value++; };
        double operator--(int) { return value--; };
        template<typename T>
        double operator+(const T& obj) { return value + obj; };
        template<typename T>
        double operator-(const T& obj) { return value - obj; };
        template<typename T>
        double operator*(const T& obj) { return value * obj; };
        template<typename T>
        double operator/(const T& obj) { return value / obj; };
        template<typename T>
        double operator%(const T& obj) { return value % obj; };
        
    private:
        double value { 0.0 };
    };
    using spDouble = std::shared_ptr<Double>;
    
    struct String : public Type<std::string>
    {
        String() = default;
        String(std::string s) { value = s; };
        
        std::string& get() override { return value; };
        void set(std::string s) override { value = s; };
        LangType getType() const override { return LangType::STRING; };
        std::string toString() const override { return value; };
        
    private:
        std::string value;
    };
    using spString = std::shared_ptr<String>;
    
    // struct Struct {};
    //
    // struct Trait {};
     
    struct Function;
    using spFunction = std::shared_ptr<Function>;
    using Value = boost::variant< spInteger, spDouble, spString, spFunction >;
    using Parameter = std::tuple<std::string, Value>;
        
    struct FunctionDef
    {
        std::string name;
        std::vector<Parameter> parameters;
        std::string code;
        Value return_value;
    };
    
    struct Function : public Type<FunctionDef>
    {
        FunctionDef& get() override { return value; };
        void set(FunctionDef f) override { value = f; };
        LangType getType() const override { return LangType::FUNCTION; };
        std::string toString() const override { return value.name; };
        
    private:
        FunctionDef value;
    };
}