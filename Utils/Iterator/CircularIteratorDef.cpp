#include "CircularIntIterator.h"

CircularIntIterator::CircularIntIterator(pointer ptr, size_t size) : m_ptr(ptr), m_begin(ptr), m_size(size) {}

CircularIntIterator::reference CircularIntIterator::operator*() const {
    return *m_ptr;
}

CircularIntIterator::pointer CircularIntIterator::operator->() const {
    return m_ptr;
}

CircularIntIterator& CircularIntIterator::operator++() {
    ++m_ptr;
    if(m_ptr == m_begin + m_size) {
        m_ptr = m_begin;
    }
    return *this;
}

CircularIntIterator CircularIntIterator::operator++(int) {
    CircularIntIterator tmp = *this;
    ++(*this);
    return tmp;
}

bool operator==(const CircularIntIterator& lhs, const CircularIntIterator& rhs) {
    return lhs.m_ptr == rhs.m_ptr;
}

bool operator!=(const CircularIntIterator& lhs, const CircularIntIterator& rhs) {
    return lhs.m_ptr != rhs.m_ptr;
}
