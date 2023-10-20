#pragma once
#include <iostream>
class BigInt
{
private:
    int32_t *digits_array;
    bool is_negative;
    int32_t block_counter;
    //Будем хранить 9 разрядов в одном элементе массива
    static const int32_t DEGREE_BASE = 4;
    static const int32_t BASE = 1e4;


public:
    explicit BigInt(std::string str_num);
    BigInt(int32_t* digits_array, int32_t block_counter, bool is_negative);
    explicit BigInt(int32_t data);
    BigInt(const BigInt &copied);
    BigInt(BigInt&& moved);
    size_t getLen() const;
    friend std::ostream &operator<<(std::ostream &out, BigInt &num);
    BigInt operator+(BigInt const &rhs) const;
    BigInt operator-(BigInt const &rhs) const;
    BigInt operator*(BigInt const &rhs) const;
    BigInt operator+(int32_t rhs);
    BigInt operator-(int32_t rhs);
    BigInt operator*(int32_t rhs);
    BigInt operator -() const;
    bool operator==(BigInt const &rhs) const;
    bool operator>=(BigInt const &rhs) const;
    bool operator>(BigInt const &rhs) const;
    bool operator<=(BigInt const &rhs) const;
    bool operator<(BigInt const &rhs) const;
    bool operator!=(BigInt const &rhs) const;
    BigInt& operator=(BigInt&& moved);
    BigInt& operator=(const BigInt& copied);
    int32_t* getDigitsArray ();


};