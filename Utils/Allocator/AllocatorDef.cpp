#ifndef ALLOCATOR_CPP
#define ALLOCATOR_CPP
#include "Allocator.h"

//private function
template<typename T>
void MyAllocator<T>::report(T *p, size_t size, bool alloc) const {
        std::cout << (alloc ? "Alloc" : "Dealloc")
                  << " " << sizeof(T) * size << " bytes at "
                  << std::hex << std::showbase << reinterpret_cast<void*>(p)
                  << std::dec << std::endl;
}

//public
template<typename T>
MyAllocator<T>::MyAllocator(void* buffer, size_t size) : m_buffer(buffer), m_size(size), ownsBuffer(false) {}

template<typename T>
MyAllocator<T>::MyAllocator(size_t size) : m_buffer(nullptr), m_size(size), ownsBuffer(true) {}

template<typename T>
MyAllocator<T>::~MyAllocator() {
    if (ownsBuffer) {
        ::operator delete(m_buffer);
        std::cout << "Deallocated memory from custom allocator" << std::endl;
    }
}

template<typename T>
typename MyAllocator<T>::pointer MyAllocator<T>::allocate(typename MyAllocator<T>::size_type n) {
    if (n == 0) {
        return nullptr;
    }
    pointer ptr = static_cast<pointer>(::operator new(n * sizeof(T)));
    report(ptr, n);
    return ptr;
}

template<typename T>
void MyAllocator<T>::deallocate(pointer p, size_type n) {
    if (p != nullptr && n > 0) {
        report(p, n, false);
        ::operator delete(p);
    }
}

template<typename T>
typename MyAllocator<T>::size_type MyAllocator<T>::max_size() const {
    return std::numeric_limits<std::size_t>::max();
}

template<typename T>
template<class U, class... Args>
void MyAllocator<T>::construct(U* p, Args&&... args) {
    new(p) U(std::forward<Args>(args)...);
}

template<typename T>
template<class U>
void MyAllocator<T>::destroy(U* p) {
    p->~U();
    std::cout << "Destroyed memory from custom allocator" << std::endl;
}

template<typename T>
template<class U>
bool MyAllocator<T>::operator==(const MyAllocator<U> &) const { return true; }

template<typename T>
template<class U>
bool MyAllocator<T>::operator!=(const MyAllocator<U> &) const { return false;}


#endif