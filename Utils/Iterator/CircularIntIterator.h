#pragma once
#include <iterator>

class CircularIntIterator {

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    explicit CircularIntIterator(pointer ptr, size_t size) : m_ptr(ptr), m_begin(ptr), m_size(size) {

    }

    reference operator*() const {
        return *m_ptr;
    }
    pointer operator->() const {
        return m_ptr;
    }
    CircularIntIterator& operator++() {
        ++m_ptr;
        if(m_ptr == m_begin + m_size) {
            m_ptr = m_begin;
        }
        return *this;
    }
    CircularIntIterator operator++(int) {
        CircularIntIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    friend bool operator==(const CircularIntIterator& lhs, const CircularIntIterator& rhs) {
        return lhs.m_ptr == rhs.m_ptr;
    }
    friend bool operator!=(const CircularIntIterator& lhs, const CircularIntIterator& rhs) {
        return lhs.m_ptr != rhs.m_ptr;
    }

private:
    pointer m_ptr;
    pointer m_begin;
    size_t m_size;
};