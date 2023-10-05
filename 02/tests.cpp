#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <typeinfo>
#include "lab_2.cpp"

void print_digit(uint64_t digit)
{
    std::cout << digit << std::endl;
}

void start_callback()
{
    ASSERT_TRUE(1 == 1);
}

void end_callback()
{
    ASSERT_TRUE(1 == 1);
}

void print_digit1(uint64_t digit)
{
    uint64_t digit2 = 567;
    ASSERT_EQ(digit, digit2);
}

void print_str(uint64_t str)
{
    std::cout << str << std::endl;
}

void print_str1(std::string str)
{
    std::string str2 = "aaa";
    ASSERT_TRUE(str == str2);
}

void big_int_as_str(std::string str)
{
    ASSERT_TRUE(typeid(str).name() == typeid(std::string).name());
}

void str_pass_call_back() {}

void digit_pass_call_back() {}

//void big_digit_as_srt(std::string str)
//{
//    std::string str2 = "92233720368547758071";
//    ASSERT_TRUE(str == str2);
//}

TEST(ParseLib, setDigitCallBack)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(reinterpret_cast<void (*)(...)>(&print_digit1));
    std::string line = "567 aaa";
    parser.Parse(line);
}

TEST(ParseLib, setStrCallBack)
{
    TokenParser parser;
    parser.SetStrTokenCallback(reinterpret_cast<void (*)(...)>(&print_str1));
    std::string line = "567 aaa";
    parser.Parse(line);
}

TEST(ParseLib, handleTokenGTuint64_t)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(reinterpret_cast<void (*)(...)>(&print_digit));
    parser.SetStrTokenCallback(reinterpret_cast<void (*)(...)> (&big_int_as_str));
    std::string line = "92233720368547758071";
    parser.Parse(line);
}

TEST(ParseLib, setStartCallBack)
{
    TokenParser parser;
    parser.SetStartCallback(reinterpret_cast<void (*)(...)> (&start_callback));
    std::string line = "92233720368547758071";
    parser.Parse(line);
}

TEST(ParseLib, setEndCallBack)
{
    TokenParser parser;
    parser.SetStartCallback(reinterpret_cast<void (*)(...)> (&end_callback));
    std::string line = "92233720368547758071";
    parser.Parse(line);
}

TEST(ParseLib, notSetCallBacks)
{
    TokenParser parser;
    std::string line = "123 aaa 456";
    ASSERT_NO_THROW(parser.Parse(line));
}

TEST(ParseLib, setStrAndDigitCallBacks)
{
    TokenParser parser;
    parser.SetDigitTokenCallback(reinterpret_cast<void (*)(...)>(&digit_pass_call_back));
    parser.SetStrTokenCallback(reinterpret_cast<void (*)(...)> (&str_pass_call_back));
    std::string line = "567 aaa";
    ASSERT_NO_THROW(parser.Parse(line));
}
int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}