#ifndef REVERSEARRAYINTERATOR_H
#define REVERSEARRAYINTERATOR_H

#include <iterator>

class ReverseArrayIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;

    ReverseArrayIterator(pointer ptr, size_t size);

    reference operator*() const;

    pointer operator->() const;

    ReverseArrayIterator& operator++();

    ReverseArrayIterator operator++(int);

    bool operator!=(const ReverseArrayIterator& other) const;

    bool operator==(const ReverseArrayIterator& other) const;

    ReverseArrayIterator begin();

    ReverseArrayIterator end();

private:
    pointer m_ptr;
    size_t m_size;
    size_t m_index;
};

#endif
