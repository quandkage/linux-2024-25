#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>
#include <memory>
#include <limits>
#include <new>

template <typename T>
class MyAllocator {
private:
    void* m_buffer;
    size_t m_size;
    bool ownsBuffer;

    void report(T* p, size_t size, bool alloc = true) const;

public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;

    template <class U>
    struct rebind {
        using other = MyAllocator<U>;
    };

    MyAllocator(void* buffer, size_t size);

    explicit MyAllocator(size_t size);

    ~MyAllocator();

    pointer allocate(size_type n);

    void deallocate(pointer p, size_type n);


    size_type max_size() const;

    template <class U, class... Args>
    void construct(U* p, Args&&... args);

    template <class U>
    void destroy(U* p);

    template<class U>
    bool operator==(const MyAllocator<U>&) const;

    template<class U>
    bool operator!=(const MyAllocator<U>&) const;
};

#include "AllocatorDef.cpp"

#endif
