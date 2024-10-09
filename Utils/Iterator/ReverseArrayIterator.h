#pragma once
#include <iterator>

class ReverseArrayIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    ReverseArrayIterator(pointer ptr, size_t size)
        : m_ptr(ptr), m_size(size), m_index(size) {}

    reference operator*() {
        return m_ptr[m_index - 1];
    }
    pointer operator->() {
        return &m_ptr[m_index - 1];
    }

    ReverseArrayIterator& operator++() {
        --m_index;
        return *this;
    }

    ReverseArrayIterator operator++(int) {
        ReverseArrayIterator temp = *this;
        --m_index;
        return temp;
    }

    bool operator!=(const ReverseArrayIterator& other) const {
        return m_index != other.m_index;
    }

    bool operator==(const ReverseArrayIterator& other) const {
        return m_index == other.m_index;
    }

    ReverseArrayIterator begin() {
        return ReverseArrayIterator(m_ptr, m_size);
    }

    ReverseArrayIterator end() {
        return ReverseArrayIterator(m_ptr, 0);
    }

private:
    pointer m_ptr;
    size_t m_size;
    size_t m_index;
};
