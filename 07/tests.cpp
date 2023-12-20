#include "lab_7.hpp"
#include <iostream>
#include <gtest/gtest.h>
#include <cstdlib>

TEST(MyAVL, TestAtMethod)
{
    AvlMap<int, int, int, 10> avl;

    for(int i=0; i<100; i+=10) {
        avl.insert(i, i + 999);
        ASSERT_EQ(*avl.at(i), i + 999);
        ASSERT_EQ(avl.at(i).key(), i);
    }
}

TEST(MyAVL, TestAtThrow)
{
    AvlMap<int, int, int, 10> avl;

    for(int i=0; i<100; i+=10) {
        avl.insert(i, i);
        ASSERT_THROW(avl.at(i+1).val(), std::out_of_range);
        ASSERT_THROW(avl.at(i+1).key(), std::out_of_range);
    }
}

TEST(MyAVL, InsertTwice)
{
    AvlMap<int, int, int, 100> avl;

    for(int i=0; i<100; i++) {
        ASSERT_TRUE(avl.insert(i, i));
        ASSERT_EQ(avl[i], i);
        ASSERT_TRUE(avl.insert(i, i+1));
        ASSERT_EQ(avl[i], i+1);
    }
}

TEST(MyAVL, InsertInFull_array)
{
    AvlMap<int, int, int, 1> avl;

    avl.insert(10, 10);
    ASSERT_FALSE(avl.insert(20, 20));
}


TEST(MyAVL, EraseValid)
{
    AvlMap<int, int, int, 100> avl;

    for(int i=0; i<100; i++)
        avl.insert(i, i);
    for(int i=0; i<100; i++)
        ASSERT_TRUE(avl.erase(i));
    for(int i=0; i<100; i++)
        avl.insert(i, i);
    for(int i=99; i>=0; i--)
        ASSERT_TRUE(avl.erase(i));
}

TEST(MyAVL, EraseInvalid)
{
    AvlMap<int, int, int, 1> avl;

    avl.insert(10, 10);
    ASSERT_FALSE(avl.erase(20));
}

TEST(MyAVL, FindValid)
{
    AvlMap<int, int, int, 100> avl;

    for(int i=0; i<100; i++)
        avl.insert(i, i);
    for(int i=0; i<100; i++)
        ASSERT_EQ(*avl.find(i), i);
}

TEST(MyAVL, FindInvalid)
{
    AvlMap<int, int, int, 1> avl;

    avl.insert(10, 10);
    ASSERT_NE(*avl.find(20), 20);
}

TEST(MyAVL, ContainsValid)
{
    AvlMap<int, int, int, 100> avl;

    int a;
    for(int i=0; i<100; i++)
        avl.insert(i, i);
    for(int i=0; i<100; i++)
        ASSERT_TRUE(avl.contains(i, a));
}

TEST(MyAVL, ContainsInvalid)
{
    AvlMap<int, int, int, 1> avl;
    int a;

    avl.insert(10, 10);
    ASSERT_FALSE(avl.contains(20, a));
}

TEST(MyAVL, EmptyValid)
{
    AvlMap<int, int, int, 1> avl;

    ASSERT_TRUE(avl.empty());
}

TEST(MyAVL, EmptyInvalid)
{
    AvlMap<int, int, int, 1> avl;

    avl.insert(10, 10);
    ASSERT_FALSE(avl.empty());
}

TEST(MyAVL, TestSizeChanges)
{
    AvlMap<int, int, int, 100> avl;

    for(int i=0; i<90; i++) {
        ASSERT_EQ(avl.size(), i);
        avl.insert(i, i);
        ASSERT_EQ(avl.size(), i+1);
    }
    ASSERT_EQ(avl.capacity(), 100);
}

TEST(MyAVL, TestClearMetho)
{
    AvlMap<int, int, int, 100> avl;

    for(int i=0; i<1000; i+=10)
        avl.insert(i, i);
    ASSERT_EQ(avl.size(), 100);
    avl.clear();
    ASSERT_EQ(avl.size(), 0);
}

TEST(MyAVL, TestEndOnEmptyData)
{
    AvlMap<int, int, std::uint16_t, 2048> avl;
    AvlMap<int, int, std::uint16_t, 2048>::iterator it = avl.begin();
    ASSERT_EQ(it , avl.end());
    ASSERT_EQ(it, avl.end());
}

TEST(MyAVL, TestBracketsUsage)
{
    AvlMap<int, int, int, 10> avl;

    for(int i=10; i<100; i+=10){
        avl[i] = i+1;
        ASSERT_EQ(avl[i], i+1);
        ASSERT_EQ(*avl.at(i), i+1);
    }
}

TEST(MyAVL, TestDataIntegrity)
{
    AvlMap<int, int, int, 10> avl;

    for(int i=0; i<10; i++){
        avl.insert(i, rand() % 1000);
    }
    ASSERT_TRUE(avl.check());
}

TEST(MyAVL, TestBeginEnd)
{
    AvlMap<int, int, int, 12> avl;
    int x = 10;

    for(int i=10; avl.size() < 12; i+=10) {
        avl.insert(i, i);
    }
    for (auto it = avl.begin(); it != avl.end(); it++) {
        ASSERT_EQ(*it, x);
        x += 10;
    }
}

TEST(MyAVL, TestRbeginRend)
{
    AvlMap<int, int, int, 12> avl;
    int x = 120;

    for(int i=10; avl.size() < 12; i+=10) {
        avl.insert(i, i);
    }
    for (auto it = avl.rbegin(); it != avl.rend(); it++) {
        ASSERT_EQ(*it, x);
        x -= 10;
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}