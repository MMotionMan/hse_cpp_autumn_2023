#include <gtest/gtest.h>
#include "lab_6.h"


TEST(MyFormatter, CheckNoThrow) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {1}";
    EXPECT_NO_THROW({
        a = formatter.format(a, 0, 1);
    });
}

TEST(MyFormatter, CheckCorrectFormatting) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {1}";
    std::string f_s = formatter.format(a, 12, 14);
    std::string true_string = "12, 14";
    EXPECT_EQ(f_s, true_string);
}

TEST(MyFormatter, CheckWorkBadIdxFormatExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {1a}";
    EXPECT_ANY_THROW({
        std::cout << formatter.format(a, 0, 1);
    });
}

TEST(MyFormatter, CheckTextBadIdxFormatExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {1a}";
    try {
        std::cout << formatter.format(a, 0, 1);
    }
    catch (BadFormatIdxException& exception) {
        EXPECT_STREQ("InvalidId", exception.what());
    }
}

TEST(MyFormatter, CheckWorkPassedIdxExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {}";
    EXPECT_ANY_THROW({
        std::cout << formatter.format(a, 0);
    });
}

TEST(MyFormatter, CheckTextPassedIdxExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {}";
    try {
        a = formatter.format(a, 1);
    }
    catch (PassedIdxException& exception){
        EXPECT_STREQ("No index formatter args", exception.what());
    }

}

TEST(MyFormatter, CheckWorkIncompleteConstructionExcRight) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {12341235";
    EXPECT_ANY_THROW({
        std::cout << formatter.format(a, 0);
    });
}

TEST(MyFormatter, CheckTextIncompleteConstructionExcRight) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {123412";
    try {
        a = formatter.format(a, 1);
    }
    catch (IncompleteConstructionException& exception){
        EXPECT_STREQ("Passed '}' after index num.", exception.what());
    }
}

TEST(MyFormatter, CheckWorkIncompleteConstructionExcLeft) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, 12341235}";
    EXPECT_ANY_THROW({
        std::cout << formatter.format(a, 0);
    });
}

TEST(MyFormatter, CheckTextIncompleteConstructionExcLeft) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, 123412}";
    try {
        a = formatter.format(a, 1);
    }
    catch (IncompleteConstructionException& exception){
        EXPECT_STREQ("Invalid syntax. Not met '{'.", exception.what());
    }
}

TEST(MyFormatter, CheckWorkOutOfIdxRangeExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {15}";
    EXPECT_ANY_THROW({
        std::cout << formatter.format(a, 0, 1, 2);
    });
}

TEST(MyFormatter, CheckTextOutOfIdxRangeExc) {
    std::ostringstream ss;
    Formatter formatter = Formatter(ss);
    std::string a = "{0}, {15}";
    try {
        a = formatter.format(a, 1, 2, 3);
    }
    catch (OutOfIdxRangeException& exception){
        EXPECT_STREQ("Index > formatted arguments", exception.what());
    }
}


int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}