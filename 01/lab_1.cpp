#include <iostream>
#include "lab_1.h"


// Конструкто
Allocator::Allocator() {
    start_pointer = nullptr;
    offset = 0;
    full_size = 0;
}


// Метод для создания аллокатора и выделения maxSize бит памяти.
// input: maxSize - кол-во памяти выделяемой при создании аллокатор.
// При передаче maxSize = 0, start_pointer будет присвоен nullptr
void Allocator::makeAllocator(size_t maxSize) {
    if (start_pointer != nullptr) {
        delete[] start_pointer;
        offset = 0;
    }

    if (maxSize == 0) {
        start_pointer = nullptr;
        full_size = maxSize;
    } else {
        start_pointer = new char[maxSize];
        full_size = maxSize;
    }

}

// Метод для выделения блока памяти размером size в аллокаторе.
// input: size - размер блока памяти для выделения.
// return: указатель на созданный блок памяти в аллокаторе, либо nullptr, если памяти для выделения не достаточно, или
// size = 0.
char *Allocator::alloc(size_t size) {
    if (size == 0) {
        return nullptr;
    } else if (offset + size <= full_size) {
        char *new_block = start_pointer + offset;
        offset = offset + size;
        return new_block;
    }

    return nullptr;
}

//Метод для оичистки занятой памяти в аллокаторе

void Allocator::reset() {
    offset = 0;
}

//Деструктор

Allocator::~Allocator() {
    delete[] start_pointer;
}
