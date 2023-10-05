#include <iostream>
#include <string>
#include "math.h"

class TokenParser
{
private:
    void (*StartCallback) (...);
    void (*EndCallback) (...);
    void (*DigitTokenCallback) (...);
    void (*StrTokenCallback) (...);

public:
    TokenParser();

    // Устанавливаем callback-функцию перед стартом парсинга.
    void SetStartCallback(void (*StartFunc) (...));

    // Устанавливаем callback-функцию после окончания парсинга.
    void SetEndCallback(void (*EndFunc) (...));

    // Устанавливаем callback-функцию для обработки чисел.
    void SetDigitTokenCallback(void (*DigitTokenFunc) (...));

    // Устанавливаем callback-функцию для обработки строк
    void SetStrTokenCallback(void (*StrTokenFunc) (...));
    void Parse(const std::string &str);
};

void TokenParser::SetStartCallback(void (*StartFunc) (...))
{
    TokenParser::StartCallback = StartFunc;
}

void TokenParser::SetEndCallback(void (*EndFunc) (...))
{
    TokenParser::EndCallback = EndFunc;
}

void TokenParser::SetDigitTokenCallback(void (*DigitTokenFunc) (...))
{
    TokenParser::DigitTokenCallback = DigitTokenFunc;
}

void TokenParser::SetStrTokenCallback(void (*StrTokenFunc) (...))
{
    TokenParser::StrTokenCallback = StrTokenFunc;
}

void TokenParser::Parse(const std::string &str)
{
    if (TokenParser::StartCallback)
    {
        StartCallback();
    }


    size_t len_str = str.size();
    std::string token;
    int is_num = 1;
    for (size_t i = 0; i != len_str; ++i)
    {

        if (str[i] != ' ')
        {
            if (!std::isdigit(str[i]))
            {
                is_num = 0;
            }
            token += str[i];
        }

        else
        {
            try
            {

                if (is_num && DigitTokenCallback)
                {
                    uint64_t digit_token = stoll(token);

                    DigitTokenCallback(&digit_token);
                }

                else if (!is_num && StrTokenCallback)
                {
                    StrTokenCallback(&token);
                }
                token = "";
                is_num = 1;
            }

            catch(std::out_of_range const& e)
            {
//                std::cout << "num > max num in uint64_t" << std::endl;
                if (StrTokenCallback)
                {
                    StrTokenCallback(&token);
                }
                token = "";
                is_num = 1;
            }
        }



    }

    try
    {

        if (is_num && DigitTokenCallback)
        {
            uint64_t digit_token = stoll(token);

            DigitTokenCallback(&digit_token);
        }

        else if (!is_num && StrTokenCallback)
        {
            StrTokenCallback(&token);
        }
    }

    catch(std::out_of_range const& e)
    {
//        std::cout << "num > max num in uint64_t" << std::endl;
        if (StrTokenCallback)
        {
            StrTokenCallback(&token);
        }
    }
}

TokenParser::TokenParser() {
    StartCallback= nullptr;
    EndCallback = nullptr;
    DigitTokenCallback = nullptr;
    StrTokenCallback = nullptr;
}

//int main()
//{
//    TokenParser parser;
//    std::string line;
//    while (std::getline(std::cin, line)) {
//        parser.Parse(line);
//    }
//}