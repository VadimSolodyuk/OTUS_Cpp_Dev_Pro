#pragma once

#include <algorithm>
#include <cstring>
#include <memory>
#include <cstddef>
#include <iostream>
#include <type_traits>
#include <utility>

template <typename T, class Allocator = std::allocator<T> >
class vectorContainer { 
    size_t m_size{0};
    size_t m_capacity{1};
    T*     m_data{nullptr};
    T*     m_new_data{nullptr};
    Allocator m_allocator;
public:
    vectorContainer();
    explicit vectorContainer(const T data);
    vectorContainer(const vectorContainer& vector);
    ~vectorContainer() = default;
    vectorContainer& operator=(const vectorContainer& vector);
    T& operator[](const size_t index) const;
    void push_back(const T value);
    size_t getSize() const;
    size_t getCapaciti() const;
    const char* getName() const;

    struct iterator {
        iterator(T* data, const size_t index);   
        iterator& operator++();
        iterator& operator--();
        iterator& operator+(const size_t rhs);
        iterator& operator-(const size_t rhs);
        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;
        T& operator*() const;
        size_t getIndex() const;

private:
        size_t m_index{0};
        T*     m_dataIterator{nullptr};
        T*     m_iterator{nullptr};
    };
    iterator begin();  
    iterator end();
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const vectorContainer<T>& vector);

#include "my_vectorContainer.ipp"