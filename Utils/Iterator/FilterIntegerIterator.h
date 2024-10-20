#pragma once
#include <iterator>

class FilterIntegerIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using FooPointer = bool(*)(int);

    explicit FilterIntegerIterator(pointer p, const size_t size, FooPointer predicate)
    : m_ptr(p), m_size(size), m_foo_pointer(predicate)

    {
        while (m_size > 0 && !m_foo_pointer(*m_ptr)) {
            --m_size;
            ++m_ptr;
        }
    }
    reference operator*() const {
        return *m_ptr;
    }
    pointer operator->() const {
        return m_ptr;
    }
    FilterIntegerIterator& operator++(){
        if (m_size > 0) {
            do {
                --m_size;
                ++m_ptr;
            } while (m_size > 0 && !m_foo_pointer(*m_ptr));
        }
        return *this;
    }
    FilterIntegerIterator operator++(int) {
        const FilterIntegerIterator tmp = *this;
        ++(*this);
        return tmp;
    }
    friend bool operator==(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs) {
        return lhs.m_ptr == rhs.m_ptr;
    }
    friend bool operator!=(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs) {
        return !(lhs == rhs);
    }
    FilterIntegerIterator begin() const {
        return *this;
    }
    FilterIntegerIterator end() const {
        return FilterIntegerIterator(m_ptr + m_size, 0, m_foo_pointer);
    }

private:
    pointer m_ptr;
    size_t m_size;
    FooPointer m_foo_pointer;
};