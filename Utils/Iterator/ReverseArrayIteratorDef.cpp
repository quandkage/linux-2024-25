#include "ReverseArrayIterator.h"

ReverseArrayIterator::ReverseArrayIterator(pointer ptr, size_t size) : m_ptr(ptr), m_size(size), m_index(size){}

ReverseArrayIterator::reference ReverseArrayIterator::operator*() const {
    return m_ptr[m_index - 1];
}

ReverseArrayIterator::pointer ReverseArrayIterator::operator->() const {
    return &m_ptr[m_index - 1];
}

ReverseArrayIterator &ReverseArrayIterator::operator++() {
    --m_index;
    return *this;
}

ReverseArrayIterator ReverseArrayIterator::operator++(int) {
    ReverseArrayIterator temp = *this;
    --m_index;
    return temp;
}

bool ReverseArrayIterator::operator!=(const ReverseArrayIterator &other) const {
    return m_index != other.m_index;
}

bool ReverseArrayIterator::operator==(const ReverseArrayIterator &other) const {
    return m_index == other.m_index;
}

ReverseArrayIterator ReverseArrayIterator::begin() {
    return {m_ptr, m_size};
}

ReverseArrayIterator ReverseArrayIterator::end() {
    return {m_ptr, 0};
}









