#pragma once

class Allocator {
public:
    char *start_pointer;
    size_t offset;
    size_t full_size;

    Allocator();

    void makeAllocator(size_t maxSize);

    char *alloc(size_t size);

    void reset();

    ~Allocator();
};
