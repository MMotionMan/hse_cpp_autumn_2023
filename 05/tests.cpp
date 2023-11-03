#include <gtest/gtest.h>
#include "lab_5.h"

TEST(MySerializer, CheckSave) {
    Data data_save = { 12, true, 24 };

    std::stringstream stream;

    Serializer serializer(stream);
    ASSERT_TRUE(serializer.save(data_save) == Error::NoError);
}

TEST(MySeralizer, CheckLoad) {
    Data data_save = { 13, false, 76};

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(data_save);


    Data data_load = { 14, false, true };
    Deserializer deserializer(stream);
    ASSERT_FALSE(deserializer.load(data_load) == Error::NoError);
}

TEST(MySerializer, CheckSaveAndLoadA) {
    Data data_save = { 15, true, 63 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(data_save);

    Data data_load = { 16, false, 61 };
    Deserializer deserializer(stream);
//    data_load.deserialize(deserializer);
    deserializer.load(data_load);

    uint64_t a;
    stream >> a;

    ASSERT_EQ(data_save.a, data_load.a);
}

TEST(MySerializer, CheckSaveAndLoadB) {
    Data data_save = { 17, true, 60 };

    std::stringstream stream;

    Serializer serializer(stream);
    serializer.save(data_save);

    Data data_load = { 18, false, 51 };
    Deserializer deserializer(stream);
    deserializer.load(data_load);
    ASSERT_EQ(data_save.a, data_load.a);
}

TEST(MySerializer, CheckLoadFromStringstream1) {
    Data data_load = {20, false, 43};
    auto stream = std::stringstream("");
    Deserializer deserializer(stream);
    ASSERT_TRUE(deserializer.load(data_load) == Error::CorruptedArchive);
}

TEST(MySerializer, CheckLoadFromStringstream2) {
    Data data_load = {22, false, 42};
    auto stream = std::stringstream("1 15 22");
    Deserializer deserializer(stream);
    ASSERT_TRUE(deserializer.load(data_load) == Error::CorruptedArchive);
}

TEST(MySerializer, CheckLoadFromStringStream3) {
    Data data_load = {22, false, 42};
    auto stream = std::stringstream("1 false 22");
    Deserializer deserializer(stream);
    ASSERT_FALSE(deserializer.load(data_load) == Error::CorruptedArchive);
}

int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}