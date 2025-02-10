#ifndef CIRCULARITERATOR_H
#define CIRCULARITERATOR_H

#include <iterator>

class CircularIntIterator {

public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    explicit CircularIntIterator(pointer ptr, size_t size);

    reference operator*() const;

    pointer operator->() const;

    CircularIntIterator& operator++();

    CircularIntIterator operator++(int);

    friend bool operator==(const CircularIntIterator& lhs, const CircularIntIterator& rhs);
    friend bool operator!=(const CircularIntIterator& lhs, const CircularIntIterator& rhs);

private:
    pointer m_ptr;
    pointer m_begin;
    size_t m_size;
};

#endif