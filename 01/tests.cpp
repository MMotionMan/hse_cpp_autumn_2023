#include <gtest/gtest.h>
#include <iostream>
#include "lab_1.cpp"

// Пытаемся выделить память для maxSize = 0 и аллоцирвоать 1 байт
TEST (MyAllocator, Size_EQ_zero) {
    Allocator al;
    al.makeAllocator(0);
    char *block_ptr = al.alloc(1);
    ASSERT_EQ(block_ptr, nullptr);
}

// Пытаемся выделить 15 байт и аллоцировать 8
TEST (MyAllocator, Size_LT_maxSize) {
    Allocator al;
    al.makeAllocator(15);
    char *block_ptr = al.alloc(8);
    ASSERT_NE(block_ptr, nullptr);
}

// Пытаемся выделить 15 байт и все их аллоцировать
TEST (MyAllocator, Size_EQ_maxSize) {
    Allocator al;
    al.makeAllocator(15);
    char *block_ptr = al.alloc(15);
    ASSERT_NE(block_ptr, nullptr);
}

// Пытаемся аллоцировать больше байт, чем выделено
TEST (MyAllocator, Size_GT_maxSize) {
    Allocator al;
    al.makeAllocator(15);
    char *block_ptr = al.alloc(17);
    ASSERT_TRUE(block_ptr == nullptr);
}

// Делаем две аллокации и сравниваем указатели на 1-й и 2-й блоки
TEST (MyAllocator, TwoAlloc) {
    Allocator al;
    al.makeAllocator(20);
    char *first_block_ptr = al.alloc(5);
    char *second_block_ptr = al.alloc(10);
    ASSERT_GT(second_block_ptr, first_block_ptr);
}

// Проверяем, что после выполнения reset, offset = 0
TEST (MyAllocator, ResetTest) {
    Allocator al;
    al.makeAllocator(20);
    al.alloc(10);
    al.reset();
    size_t zero_value = 0;
    ASSERT_EQ(al.offset, zero_value);
}

// Проверяем, что после второй аллокации, выделяется новое количество памяти
TEST (MyAllocator, TwoMakeAllocator) {
    Allocator al;
    size_t first_size = 20;
    al.makeAllocator(first_size);
    size_t second_size = 30;
    al.makeAllocator(second_size);
    ASSERT_EQ(al.full_size, second_size);
}

int main() {
    ::testing::InitGoogleTest();

    return RUN_ALL_TESTS();
}