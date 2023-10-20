#include <gtest/gtest.h>
#include <iostream>
#include "lab_4.cpp"
#include <fstream>


TEST(MyBigInt, CopyTest) {
    std::string num = "100";
    BigInt big_num = BigInt(num);
    BigInt big_num2 = big_num;
    for (size_t i = 0; i < big_num.getLen(); ++i) {
        ASSERT_EQ(big_num.getDigitsArray()[i], big_num2.getDigitsArray()[i]);
    }
}

TEST(MyBigInt, OstreamTest) {
    std::string num = "100";

    BigInt big_num = BigInt(num);

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << big_num;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);
    int32_t int_num = 100;

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_TRUE(file_value == int_num);
}

TEST(MyBigInt, SumBigIntTest) {
    std::string num = "10000";
    int32_t int_num = 10000;
    int32_t res = int_num + int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum2 = BigInt(num);
    BigInt bigNum3 = bigNum1 + bigNum2;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum3;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);

}

TEST(MyBigInt, MinusBigIntTest) {
        std::string num = "10000";
        int32_t int_num = 10000;
        int32_t res = int_num - int_num;
        BigInt bigNum1 = BigInt(num);
        BigInt bigNum2 = BigInt(num);
        BigInt bigNum3 = bigNum1 - bigNum2;

        std::ofstream out("testing_file.bin", std::ios::binary);

        if (out.is_open()) {
            out << bigNum3;
        }

        out.close();

        std::ifstream in("testing_file.bin", std::ios::binary);

        int file_value;
        in >> file_value;

        remove("testing_file.bin");

        ASSERT_EQ(res, file_value);
}

TEST(MyBigInt, MultBigIntTest) {
    std::string num = "50";
    int32_t int_num = 50;
    int32_t res = int_num * int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum2 = BigInt(num);
    BigInt bigNum3 = bigNum1 * bigNum2;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum3;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);
}

TEST(MyBigInt, SumIntTest) {
    std::string num = "50";
    int32_t int_num = 50;
    int32_t res = int_num + int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum3 = bigNum1 + int_num;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum3;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);
}

TEST(MyBigInt, DiffIntTest) {
    std::string num = "50";
    int32_t int_num = 50;
    int32_t res = int_num - int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum3 = bigNum1 - int_num;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum3;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);
}

TEST(MyBigInt, MultIntTest) {
    std::string num = "50";
    int32_t int_num = 50;
    int32_t res = int_num * int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum3 = bigNum1 * int_num;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum3;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);
}

TEST(MyBigInt, EqualTest1) {
    std::string num = "100";
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum2 = BigInt(num);

    ASSERT_TRUE(bigNum1 == bigNum2);
}

TEST(MyBigInt, EqualTest2) {
    std::string num1 = "100000000";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_FALSE(bigNum1 == bigNum2);
}

TEST(MyBigInt, NotEqualTest1) {
    std::string num1 = "100000000";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 != bigNum2);
}

TEST(MyBigInt, NotEqualTest2) {
    std::string num1 = "100";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_FALSE(bigNum1 != bigNum2);
}

TEST(MyBigInt, LTTest1) {
    std::string num1 = "100";
    std::string num2 = "1000";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 < bigNum2);
}

TEST(MyBigInt, LTTest2) {
    std::string num1 = "100";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_FALSE(bigNum1 < bigNum2);
}

TEST(MyBigInt, LETest1) {
    std::string num1 = "100";
    std::string num2 = "1000";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 <= bigNum2);
}

TEST(MyBigInt, LETest2) {
    std::string num1 = "100";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 <= bigNum2);
}

TEST(MyBigInt, LETest3) {
    std::string num1 = "1000";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_FALSE(bigNum1 <= bigNum2);
}

TEST(MyBigInt, GTTest1) {
    std::string num1 = "10000";
    std::string num2 = "1000";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 > bigNum2);
}

TEST(MyBigInt, GTTest2) {
    std::string num1 = "100";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_FALSE(bigNum1 > bigNum2);
}

TEST(MyBigInt, GETest1) {
    std::string num1 = "10000";
    std::string num2 = "1000";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 >= bigNum2);
}

TEST(MyBigInt, GETest2) {
    std::string num1 = "100";
    std::string num2 = "100";
    BigInt bigNum1 = BigInt(num1);
    BigInt bigNum2 = BigInt(num2);

    ASSERT_TRUE(bigNum1 >= bigNum2);
}


TEST(MyBigInt, UnMinusTest) {
    std::string num = "50";
    int32_t int_num = 50;
    int32_t res = -int_num;
    BigInt bigNum1 = BigInt(num);
    BigInt bigNum2 = -bigNum1;

    std::ofstream out("testing_file.bin", std::ios::binary);

    if (out.is_open()) {
        out << bigNum2;
    }

    out.close();

    std::ifstream in("testing_file.bin", std::ios::binary);

    int file_value;
    in >> file_value;

    remove("testing_file.bin");

    ASSERT_EQ(res, file_value);
}



int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}