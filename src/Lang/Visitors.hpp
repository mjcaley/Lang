#pragma once
#include <vector>
#include "Lang/AST.hpp"
#include "StackMachine/StackMachineFile.hpp"


namespace Lang { namespace AST {
    
    struct LiteralVisitor : public boost::static_visitor<>
    {
        LiteralVisitor(std::vector<int32_t>& byte_code) : byte_code(byte_code) {}
    
        void operator()(const IntegerLiteral& integer_lit) const;
        void operator()(const LongLiteral& long_lit) const;
        void operator()(const FloatLiteral& float_lit) const;
        void operator()(const DoubleLiteral& double_lit) const;
        void operator()(const StringLiteral& string_lit) const;
        
    private:
        std::vector<int32_t>& byte_code;
    };
    
    struct LHSVisitor : public boost::static_visitor<>
    {
        LHSVisitor(std::vector<int32_t>& byte_code) : byte_code(byte_code) {}
        
        void operator()(const Variable& var) const;
        
    private:
        std::vector<int32_t>& byte_code;
    };
    
    struct RHSVisitor : public boost::static_visitor<>
    {
        RHSVisitor(std::vector<int32_t>& byte_code) : byte_code(byte_code) {}
        
        void operator()(const Literal& var) const;
        
    private:
        std::vector<int32_t>& byte_code;
    };
    
    struct TokenVisitor : public boost::static_visitor<>
    {
        TokenVisitor(std::vector<int32_t>& byte_code) : byte_code(byte_code) {}
        
        void operator()(const LHS& lhs) const;
        void operator()(const RHS& rhs) const;
        
    private:
        std::vector<int32_t>& byte_code;
    };
    
    std::unique_ptr<StackMachine::StackMachineFile> generate(Program& ast);
    
} }