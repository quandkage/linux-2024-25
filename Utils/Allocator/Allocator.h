#pragma once

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

    void report(T* p, size_t size, bool alloc = true) const {
        std::cout << (alloc ? "Alloc" : "Dealloc")
                  << " " << sizeof(T) * size << " bytes at "
                  << std::hex << std::showbase << reinterpret_cast<void*>(p)
                  << std::dec << std::endl;
    }

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

    MyAllocator(void* buffer, size_t size) : m_buffer(buffer), m_size(size), ownsBuffer(false)  {}

    explicit MyAllocator(size_t size) : m_buffer(nullptr), m_size(size), ownsBuffer(true) {}

    ~MyAllocator() {
        if (ownsBuffer) {
            ::operator delete(m_buffer);
            std::cout << "Deallocated memory from custom allocator" << std::endl;
        }
    }

    pointer allocate(size_type n) {
        if (n == 0) {
            return nullptr;
        }
        pointer ptr = static_cast<pointer>(::operator new(n * sizeof(T)));
        report(ptr, n);
        return ptr;
    }

    void deallocate(pointer p, size_type n) {
        if (p != nullptr && n > 0) {
            report(p, n, false);
            ::operator delete(p);
        }
    }


    size_type max_size() const {
        return std::numeric_limits<std::size_t>::max();
    }

    template <class U, class... Args>
    void construct(U* p, Args&&... args) {
        new(p) U(std::forward<Args>(args)...);
    }

    template <class U>
    void destroy(U* p) {
        p->~U();
        std::cout << "Destroyed memory from custom allocator" << std::endl;
    }

    template<class U>
    bool operator==(const MyAllocator<U>&) const { return true; }

    template<class U>
    bool operator!=(const MyAllocator<U>&) const { return false; }
};
