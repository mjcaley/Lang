#include <catch.hpp>

#include <fstream>
#include "LangFile.hpp"
#include "FileFormatException.hpp"
#include "FileNotFoundException.hpp"
#include "Bytecode/InstructionSet.hpp"

using namespace Lang;


TEST_CASE( "LangFile opens file", "[LangFile]" )
{
    REQUIRE_NOTHROW(LangFile::create("LangFile-blank_compiled.lang") );
}

TEST_CASE( "LangFile created with default options", "[LangFile]" )
{
    auto lf = LangFile::create();
    
    REQUIRE(lf->version == 1);
}

TEST_CASE( "LangFile throws exception with incorrect format", "[LangFile]" )
{
    REQUIRE_THROWS_AS(LangFile::create("LangFile-bad_format.lang"),
                      Exception::FileFormatException);
}

TEST_CASE( "LangFile throws exception for file not found", "[LangFile]" )
{
    REQUIRE_THROWS_AS(LangFile::create("LangFile-fake_name.lang"),
                      Exception::FileNotFoundException);
}

TEST_CASE( "LangFile test if valid", "[LangFile]" )
{
    auto lf = LangFile::create("LangFile-blank_compiled.lang");
    REQUIRE(LangFile::isValid(lf->byte_code.begin(),
                              lf->byte_code.end()) == true);
}

TEST_CASE( "LangFile writes file", "[LangFile]" )
{
    std::string filename = "LangFile-write_compiled.lang";
    
    auto lf = LangFile::create();
    lf->version = 1;
    lf->byte_code = { PUSH, (int32_t)3, PUSH, (int32_t)4, MUL, PRNT, HALT };
    bool result = lf->write(filename);
    REQUIRE(result == true);
    
    std::ifstream in(filename, std::ios::binary);
    REQUIRE(in.is_open() == true);
}

TEST_CASE( "LangFile length", "[LangFile]" )
{
    auto lf = LangFile::create("LangFile-blank_compiled.lang");
    REQUIRE(lf->length() == 0);
}