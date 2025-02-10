#ifndef FILTERINTEGERITERATOR_H
#define FILTERINTEGERITERATOR_H
#include <iterator>

class FilterIntegerIterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type = std::ptrdiff_t;
    using value_type = int;
    using pointer = int*;
    using reference = int&;
    using FooPointer = bool(*)(int);

    explicit FilterIntegerIterator(pointer p, size_t size, FooPointer predicate);

    reference operator*() const;

    pointer operator->() const;

    FilterIntegerIterator& operator++();

    FilterIntegerIterator operator++(int);

    friend bool operator==(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs);
    friend bool operator!=(const FilterIntegerIterator& lhs, const FilterIntegerIterator& rhs);

    [[nodiscard]] FilterIntegerIterator begin() const;

    [[nodiscard]] FilterIntegerIterator end() const;

private:
    pointer m_ptr;
    size_t m_size;
    FooPointer m_foo_pointer;
};

#endif