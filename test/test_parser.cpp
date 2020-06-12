#include "linear_components.hpp"
#include "parser.hpp"

#include <gtest/gtest.h>

using namespace std;

TEST(parser_test, parser_parse_number)
{
    vector<string> numbers_string{
        "0.1p", // "0.1p" will cause error in MacOS but "0.1 p" will not.
        "1.1n", // "1.1n" will cause error in MacOS but "1.1 n" will not.
        "1.1µ",
        "1.1m",
        "1.1",
        "1.1k",
        "1.1Meg",
        "0",
        "010",
        "000",
        "0k",
        "01k",
    };
    vector<double> numbers_double = {
        0.1e-12,
        1.1e-9,
        1.1e-6,
        1.1e-3,
        1.1,
        1.1e3,
        1.1e6,
        0.0,
        10.0,
        0.0,
        0.0,
        1.0e3,
    };
    for (int i = 0; i < numbers_string.size(); i++)
    {
        EXPECT_DOUBLE_EQ(parse_number(numbers_string[i]), numbers_double[i]) << numbers_string[i];
    };
    vector<string> numbers_string2 = {
        "",
        "k",
        "a",
    };
    for (int i = 0; i < numbers_string2.size(); i++)
    {
        ASSERT_DEATH(parse_number(numbers_string2[i]), "Assert|ERROR") << numbers_string2[i];
    }
}

TEST(parser_test, parser_is_comment)
{
    string input = "* this is a comment";
    string input2 = ".* this is a comment";
    EXPECT_TRUE(is_comment(input)) << "* this is a comment";
    EXPECT_FALSE(is_comment(input2)) << ".* this is a comment";
}

TEST(parser_test, parser_is_directive)
{
    string input = ".something";
    string input2 = ". something";
    EXPECT_TRUE(is_directive(input)) << ".something";
    EXPECT_TRUE(is_directive(input2)) << ". something";
}

TEST(parser_test, parser_is_tran)
{
    string input = ".tran";
    string input2 = ". tran";
    EXPECT_TRUE(is_tran(input)) << ".tran";
    EXPECT_FALSE(is_tran(input2)) << ". tran";
}

TEST(parser_test, parser_is_end)
{
    string input = ".end";
    string input2 = ". end";
    EXPECT_TRUE(is_end(input)) << ".end";
    EXPECT_FALSE(is_end(input2)) << ". end";
}

TEST(parser_test, parser_is_component)
{
    string input = ".end";
    string input2 = ".tran";
    string input3 = "*tran";
    string input4 = ". end";
    string input5 = "V1 N003 0 SINE(2 1 1000)";
    EXPECT_FALSE(is_component(input)) << ".end";
    EXPECT_FALSE(is_component(input2)) << ".tran";
    EXPECT_FALSE(is_component(input3)) << "*tran";
    EXPECT_FALSE(is_component(input4)) << ". end";
    EXPECT_TRUE(is_component(input5)) << "V1 N003 0 SINE(2 1 1000)";
}

TEST(parser_test, parser_parse_component)
{
    vector<string> components_string = {"V1 N003 0 2",
                                        "V1 N003 0 SINE(2 1 1000)",
                                        "R1 N001 N003 1k",
                                        "C1 N001 0 1μ ",
                                        "L1 N002 N001 1m",
                                        "R2 N002 N001 1Meg "};
    vector<string> components_name = {
        "V1",
        "V1",
        "R1",
        "C1",
        "L1",
        "R2",
    };
    vector<Component *> components;
    vector<Node *> nodes;
    for (auto it = components_string.begin(); it != components_string.end(); it++)
    {
        components.push_back(parse_component(*it, nodes));
    }
    for (int i = 0; i < components.size(); i++)
    {
        EXPECT_EQ(components[i]->get_name(), components_name[i]) << components_name[i];
    }
}

TEST(parser_test, parser_parse_tran)
{
    string input = ".tran 0 10ms 0 1us";
    string input2 = ".tran 0 5ms 0 1µs";
    vector<double> output = parse_tran(input);
    vector<double> output2 = parse_tran(input2);
    vector<double> ref = {1.0e-6, 1.0e-2};
    vector<double> ref2 = {1.0e-6, 5.0e-3};
    EXPECT_EQ(output, ref) << input;
    EXPECT_EQ(output2, ref2) << input2;
}

int main(int argc, char **argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
};
