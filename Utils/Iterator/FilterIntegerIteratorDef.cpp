#include "FilterIntegerIterator.h"

FilterIntegerIterator::FilterIntegerIterator(pointer p, const size_t size, FooPointer predicate)
    : m_ptr(p), m_size(size), m_foo_pointer(predicate)
{
    while (m_size > 0 && !m_foo_pointer(*m_ptr)) {
        --m_size;
        ++m_ptr;
    }
}

FilterIntegerIterator::reference FilterIntegerIterator::operator*() const {
    return *m_ptr;
}

FilterIntegerIterator::pointer FilterIntegerIterator::operator->() const {
    return m_ptr;
}

FilterIntegerIterator &FilterIntegerIterator::operator++() {
    if (m_size > 0) {
        do {
            --m_size;
            ++m_ptr;
        } while (m_size > 0 && !m_foo_pointer(*m_ptr));
    }
    return *this;
}

FilterIntegerIterator FilterIntegerIterator::operator++(int) {
    const FilterIntegerIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool operator==(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs) {
    return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs) {
    return !(lhs == rhs);
}

FilterIntegerIterator FilterIntegerIterator::begin() const {
    return *this;
}

FilterIntegerIterator FilterIntegerIterator::end() const {
    return FilterIntegerIterator(m_ptr + m_size, 0, m_foo_pointer);
}





