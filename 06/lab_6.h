#pragma once
#include <string>
#include <exception>
#include <sstream>

class BadFormatIdxException : public std::exception {
private:
    std::string error_message;
public:
    BadFormatIdxException(std::string_view error) : error_message(error) {};

    const char* what() const noexcept override {
        return error_message.c_str();
    }
};

class PassedIdxException : public std::exception {
private:
    std::string error_message;
public:
    PassedIdxException(std::string_view error) : error_message(error) {};

    const char* what() const noexcept override {
        return error_message.c_str();
    }
};

class IncompleteConstructionException : public std::runtime_error {
public:
    IncompleteConstructionException(const std::string &error) : std::runtime_error(error.c_str()) {}
};

class OutOfIdxRangeException : public std::runtime_error {
private:
    std::string error_message;
public:
    OutOfIdxRangeException(const std::string &error) : std::runtime_error(error.c_str()) {}
};



class Formatter {
private:
    std::ostringstream& formatted_str_;
public:

    Formatter(std::ostringstream& formatted_str) : formatted_str_(formatted_str){};

    template<class T>
    std::string args_to_string(T&& x);
    template<class... argsT>
    std::string format(std::string str, argsT&&... args);

};

#include "lab_6.hpp"