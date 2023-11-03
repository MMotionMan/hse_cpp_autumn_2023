#pragma once
#include "fstream"
#include "iostream"
enum Error
{
    NoError,
    CorruptedArchive
};

struct Data
{
    uint64_t a;
    bool b;
    uint64_t c;

    template <class Serializer>
    Error serialize(Serializer& serializer)
    {
        return serializer(a, b, c);
    }

    template <class Deserializer>
    Error deserialize(Deserializer& deserializer)
    {
        return deserializer(a, b, c);
    }
};

class Serializer {
    static constexpr char Separator = ' ';
    std::ostream& out_;

public:
    explicit Serializer(std::ostream& out) : out_(out) {}


      template <class T>
      Error save(T& object) {
          return object.serialize(*this);
      }

      template <class... ArgsT>
      Error operator()(ArgsT... args) {
          return out_in_stream(std::forward<ArgsT&>(args)...);
      }

    template<class T>
    Error out_in_stream(T&& val);

    template<class T, class... Args>
    Error out_in_stream(T&& val, Args&&... args);

    Error process(bool arg);
    Error process(uint64_t arg);
};

class Deserializer {
    std::istream& in_;
    static constexpr char Separator = ' ';

public:
    explicit Deserializer(std::istream& in) : in_(in) {}

    template<class T>
    Error load(T& object) {
        return object.deserialize(*this);
    }

    template<class... ArgsT>
    Error operator()(ArgsT&... args) {
        return load_on_stream(std::forward<ArgsT&>(args)...);
    }

private:
    template<class T>
    Error load_on_stream(T& value);

    template<class T, class... Args>
    Error load_on_stream(T& value, Args&... args);

    Error process(bool& value);
    Error process(uint64_t& value);

};
#include "lab_5.hpp"
