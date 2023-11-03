#pragma once
#include "lab_5.h"

template <class T>
Error Serializer::out_in_stream(T &&val) {
        return process(val);
}

template <class T, class... Args>
Error Serializer::out_in_stream(T &&val, Args &&...args) {
    if (out_in_stream(val) == Error::CorruptedArchive) {
        return Error::CorruptedArchive;
    }

    return Serializer::out_in_stream(std::forward<Args>(args)...);
}

Error Serializer::process(bool arg) {
    Serializer::out_ << arg << Serializer::Separator;
    return  (out_) ? Error::NoError : Error::CorruptedArchive;
}

Error Serializer::process(uint64_t arg) {
    Serializer::out_ << arg << Serializer::Separator;
    return  (out_) ? Error::NoError : Error::CorruptedArchive;
}

template<class T>
Error Deserializer::load_on_stream(T& value) {
    return Deserializer::process(value);
}

template<class T, class... Args>
Error Deserializer::load_on_stream(T& value, Args&... args) {
    if (load_on_stream(value) == Error::CorruptedArchive) {
        return Error::CorruptedArchive;
    }

    return Deserializer::load_on_stream(std::forward<Args&>(args)...);
}

Error Deserializer::process(bool& value) {
    in_ >> std::boolalpha >> value;
    return (in_) ? Error::NoError : Error::CorruptedArchive;
}

Error Deserializer::process(uint64_t& value) {
    in_ >> value;
    return (in_) ? Error::NoError : Error::CorruptedArchive;
}