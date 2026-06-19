#include <catch2/catch_test_macros.hpp>

#include "CLIParser.h"

TEST_CASE("Parser test")
{
    char a0[] = "sound_processor";
    char a1[] = "-i";
    char a2[] = "in.wav";
    char a3[] = "-o";
    char a4[] = "out.wav";
    char a5[] = "-f";
    char a6[] = "ampl";
    char a7[] = "0.5";

    char* argv[] = {a0, a1, a2, a3, a4, a5, a6, a7};

    ArgsParser parser;

    auto result = parser.parse(8, argv);

    REQUIRE(result == ArgsParser::Result::ok);
    REQUIRE(std::string(parser.getInFileName()) == "in.wav");
    REQUIRE(std::string(parser.getOutFileName()) == "out.wav");
    REQUIRE(parser.getFilterDescriptors().size() == 1);
    REQUIRE(std::string(parser.getFilterDescriptors()[0].name) == "ampl");
    REQUIRE(std::string(parser.getFilterDescriptors()[0].params[0]) == "0.5");
}