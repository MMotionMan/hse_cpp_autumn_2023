#pragma once
#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#include "lab_6.h"

template<class T>
std::string Formatter::args_to_string(T &&x) {
    std::stringstream ss;
    ss << x;
    return ss.str();
}

template<class ...argsT>
std::string Formatter::format(std::string str_form, argsT &&...args) {
    std::vector<std::string> str_args {Formatter::args_to_string(std::forward<argsT>(args))...};
    int format_idx = 0;
    for (size_t i = 0; i < str_form.length(); ++i) {
        if (str_form[i] == '{') {
            i++;

            if (str_form[i] == '}') {
                throw PassedIdxException("No index formatter args");
            }
            int num_place = 0;
            while (str_form[i] != '}' && i < str_form.length()) {
                if (isdigit(str_form[i])) {
                    format_idx += (str_form[i] - '0') * static_cast<int32_t> (pow(10, num_place));
                    i++;
                    num_place ++;
                }
                else {
                    throw BadFormatIdxException("InvalidId");
                }
            }

            if (i == str_form.length()) {
                throw IncompleteConstructionException("Passed '}' after index num.");
            }

            if (format_idx < static_cast<int>(str_args.size())) {
                Formatter::formatted_str_ << str_args[format_idx];
                format_idx = 0;
            }
            else {
                throw OutOfIdxRangeException("Index > formatted arguments");
            }


        }

        else if (str_form[i] == '}') {
            throw IncompleteConstructionException("Invalid syntax. Not met '{'.");
        }

        else {
            Formatter::formatted_str_ << str_form[i];
        }
    }

    return Formatter::formatted_str_.str();
}