#include "lab_4.h"
#include <cmath>

BigInt::BigInt(std::string str_num) : is_negative(false), block_counter(0){
    if (str_num.length() == 0) {
        this -> digits_array = nullptr;
    } else {
        int32_t num_length;
        num_length = static_cast<int32_t> (str_num.length());


        if (num_length % BigInt::DEGREE_BASE == 0) {
            this -> block_counter = num_length / BigInt::DEGREE_BASE;
            this -> digits_array = new int32_t[block_counter];

        } else {
            this -> block_counter = (num_length / BigInt::DEGREE_BASE) + 1;
            this -> digits_array = new int32_t[block_counter];
        }

        if (str_num[0] == '-') {
            this -> is_negative = true;
        }

        size_t dig_len = 0;
        int32_t dig_block = 0;
        size_t num_block = 0;

        for (int32_t idx = num_length - 1; idx >= this -> is_negative; --idx) {
            dig_block += (str_num[idx] - '0') * static_cast<int32_t> (pow(10, dig_len));

            if (dig_len == BigInt::DEGREE_BASE - 1 || idx == this -> is_negative) {
                this -> digits_array[num_block] = dig_block;
                ++num_block;
                dig_len = 0;
                dig_block = 0;
            } else {
                dig_len++;
            }
        }
    }
}

BigInt::BigInt(const BigInt& copied) {
    this -> digits_array = copied.digits_array;
    this -> is_negative = copied.is_negative;
    this -> block_counter = copied.block_counter;
}

BigInt& BigInt::operator=(const BigInt& copied) {
    return *this;
}

BigInt::BigInt(BigInt&& moved) {
    this -> digits_array = moved.digits_array;
    this -> is_negative = moved.is_negative;
    this -> block_counter = moved.block_counter;
}

BigInt& BigInt::operator=(BigInt&& moved) {
    if (&moved == this) {
        return *this;
    }

    this -> digits_array = moved.digits_array;
    this -> is_negative = moved.is_negative;
    this -> block_counter = moved.block_counter;

    delete[] moved.digits_array;

    return *this;

}

BigInt::BigInt(int32_t* digits_array, int32_t block_counter, bool is_negative) : digits_array(digits_array),
                                                                block_counter(block_counter), is_negative(is_negative){}

BigInt::BigInt(int32_t data)
{
    this -> block_counter = data / BigInt::BASE + 1;
    this -> digits_array = new int32_t[block_counter];
    int32_t new_block_idx = 0;
    int32_t new_block = 0;
    int32_t new_block_c = 0;
    while (data > 0) {
        int32_t symbol = data % 10;
        new_block += symbol * static_cast<int32_t> (std::pow(10,new_block_c));
        data = data / 10;
        new_block_c++;
        if (data == 0 || new_block_c >= BigInt::BASE) {
            this -> digits_array[new_block_idx] = new_block;
            new_block_c = (data >= BigInt::BASE ? BigInt::DEGREE_BASE : 3);
            new_block = 0;
            new_block_idx++;
        }

    }
}

size_t BigInt::getLen() const {
    return this -> block_counter;
}

bool BigInt::operator==(BigInt const &rhs) const {
    if (this -> block_counter != rhs.getLen()) {
        return false;
    }

    for (int32_t i = this -> block_counter - 1; i >= 0; --i)
    {
        if (this -> digits_array[i] != rhs.digits_array[i]) {
            return false;
        }
    }

    return true;
}

bool BigInt::operator!=(BigInt const &rhs) const {
    return !BigInt::operator==(rhs);
}

bool BigInt::operator>(BigInt const &rhs) const {
    if (this -> block_counter > rhs.getLen()) {
        return true;
    } else if (this -> block_counter < rhs.getLen()) {
        return false;
    }

    for (int32_t i = this -> block_counter - 1; i >= 0; --i) {
        if (this -> digits_array[i] < rhs.digits_array[i]) {
            return false;
        } else if (this -> digits_array[i] > rhs.digits_array[i]) {
            return true;
        }
    }

    return false;
}

bool BigInt::operator>=(BigInt const &rhs) const {
    return (BigInt::operator>(rhs) || BigInt::operator==(rhs));
}

bool BigInt::operator<(BigInt const &rhs) const {
    return !BigInt::operator>=(rhs);
}

bool BigInt::operator<=(BigInt const &rhs) const {
    return (BigInt::operator==(rhs) || BigInt::operator<(rhs));
}

std::ostream &operator<<(std::ostream &out, BigInt &num) {
    if (num.is_negative) {
        out << '-';
    }

    for (int32_t i = num.block_counter - 1; i >= 0; --i) {
        if (num.digits_array[i] == 0) {
            for (int32_t j = 0; j < BigInt::DEGREE_BASE; ++j) {
                out << 0;
            }
        } else {
            out << num.digits_array[i];
        }

    }

    return out;
}

BigInt BigInt::operator+(BigInt const &rhs) const {
    BigInt res = BigInt(this->digits_array, this->block_counter, this->is_negative);
    if (this->is_negative && !rhs.is_negative) {
        return rhs - *this;
    } else if (rhs.is_negative && !(this -> is_negative)) {
        return *this - rhs;
    }

    int overflow = 0;

    for (int32_t i = 0; i < std::max(rhs.block_counter, this -> block_counter); ++i) {
        res.digits_array[i] = overflow + this -> digits_array[i] + rhs.digits_array[i];

        overflow = res.digits_array[i] >= BigInt::BASE;
        if (overflow != 0) {
            res.digits_array[i] -= BigInt::BASE;
        }
    }

    if (overflow != 0) {
        int32_t* t_digit_arr;
        t_digit_arr = new int32_t[res.block_counter];

        for (int32_t i = 0; i < res.block_counter; ++i) {
            t_digit_arr[i] = res.digits_array[i];
        }

        delete[] res.digits_array;
        res.digits_array = t_digit_arr;
    }

    return res;
}

BigInt BigInt::operator-() const {
    BigInt copy(*this);
    copy.is_negative = !copy.is_negative;
    return copy;
}

BigInt BigInt::operator-(const BigInt& rhs) const {
    BigInt res = BigInt(rhs.digits_array, rhs.block_counter, rhs.is_negative);
    if (rhs.is_negative && !(this -> is_negative)) {
        res.is_negative = false;
        return *this + res;
    } else if (rhs.is_negative && this -> is_negative) {
        return *this + rhs;
    } else if (!rhs.is_negative && this -> is_negative) {
        res.is_negative = true;
        return *this + res;
    }

    if (*this < rhs) {
        return -(rhs - *this);
    }

    int32_t leading_zero = 0;

    int32_t overflow = 0;

    for (int32_t i = 0; i < std::max(rhs.block_counter, this -> block_counter); ++i) {
        res.digits_array[i] =  this -> digits_array[i] - rhs.digits_array[i] - overflow;

        if (res.digits_array[i] == 0) {
            leading_zero++;
        } else {
            leading_zero = 0;
        }

        overflow = res.digits_array[i] < 0;
        if (overflow != 0) {
            res.digits_array[i] += BigInt::BASE;
        }
    }

    if (leading_zero != 0){
        int32_t* t_digit_arr;
        int32_t new_size = res.block_counter - leading_zero;
        res.block_counter = new_size;
        t_digit_arr = new int32_t[new_size];
        for (int32_t i = 0; i < new_size; ++i) {
            t_digit_arr[i] = res.digits_array[i];
        }

        delete[] res.digits_array;
        res.digits_array = t_digit_arr;
    }
    return res;
}

BigInt BigInt::operator+(int32_t rhs) {
    BigInt res = BigInt(this->digits_array, this->block_counter, this->is_negative);

    int32_t overflow = ((res.digits_array[0] + rhs - BigInt::BASE) >= 0 ? (res.digits_array[0] + rhs - BigInt::BASE + 1) : 0);
    if (overflow > 0) {

        for (int32_t i = 0; (i < res.block_counter) && (overflow > 0); ++i) {
            res.digits_array[i] += overflow;

            res.digits_array[i] -= BigInt::BASE;

            overflow = overflow - this->digits_array[i];


        }

        if (overflow > 0) {
            int32_t *t_digit_arr;
            int32_t new_size = res.block_counter + overflow / BigInt::BASE + 1;
            t_digit_arr = new int32_t[new_size];

            for (int32_t i = 0; i < res.block_counter; ++i) {
                t_digit_arr[i] = res.digits_array[i];
            }

            for (int32_t i = res.block_counter; i < new_size; ++i) {
                t_digit_arr[i] = overflow;
                overflow = overflow - t_digit_arr[i];

                if (overflow > 0) {
                    res.digits_array[i] -= BigInt::BASE;
                }
            }

            delete[] res.digits_array;
            res.digits_array = t_digit_arr;
        }
    } else {
        res.digits_array[0] += rhs;
    }

    return res;
}

BigInt BigInt::operator-(int32_t rhs_int) {
    BigInt res = BigInt(this->digits_array, this->block_counter, this->is_negative);
    BigInt rhs = BigInt(rhs_int);
    int32_t leading_zero = 0;

    int32_t overflow = 0;

    for (int32_t i = 0; i < std::max(rhs.block_counter, this -> block_counter); ++i) {
        res.digits_array[i] =  this -> digits_array[i] - rhs.digits_array[i] - overflow;

        if (res.digits_array[i] == 0) {
            leading_zero++;
        } else {
            leading_zero = 0;
        }

        overflow = res.digits_array[i] < 0;
        if (overflow != 0) {
            res.digits_array[i] += BigInt::BASE;
        }
    }

    if (leading_zero != 0){
        int32_t* t_digit_arr;
        int32_t new_size = res.block_counter - leading_zero;
        res.block_counter = new_size;
        t_digit_arr = new int32_t[new_size];
        for (int32_t i = 0; i < new_size; ++i) {
            t_digit_arr[i] = res.digits_array[i];
        }

        delete[] res.digits_array;
        res.digits_array = t_digit_arr;
    }
    return res;
}

BigInt BigInt::operator*(BigInt const &rhs) const{
    int32_t new_size = this->block_counter + rhs.block_counter;
    BigInt res = BigInt(new int32_t[new_size], new_size, this->is_negative != rhs.is_negative);

    for (int32_t i = 0; i < this -> block_counter; ++i) {
        int carry = 0;
        for (int32_t j = 0; j < rhs.block_counter || carry != 0; ++j) {
            int32_t cur = res.digits_array[i] + this -> digits_array[i] * (j < rhs.block_counter ? rhs.digits_array[i] : 0);
            res.digits_array[i + j] = static_cast<int32_t> (cur % BigInt::BASE);
            carry = static_cast<int32_t> (cur / BigInt::BASE);
        }
    }

    return res;


}

BigInt BigInt::operator*(int32_t rhs) {
    BigInt res = BigInt(rhs);

    return *this * res;


}

int32_t* BigInt::getDigitsArray() {
    return this -> digits_array;
}