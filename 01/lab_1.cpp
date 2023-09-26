#include <iostream>
#include "lab_1.h"


Allocator::Allocator() {
    start_pointer = nullptr;
    offset = 0;
    full_size = 0;
}

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

char *Allocator::alloc(size_t size) {
    if (offset + size <= full_size) {
        char *new_block = start_pointer + offset;
        offset = offset + size;
        return new_block;
    }

    return nullptr;
}

void Allocator::reset() {
    offset = 0;
}

Allocator::~Allocator() {
    delete[] start_pointer;
}
