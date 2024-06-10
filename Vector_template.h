#ifndef VECTOR_TEMPLATE_H_INCLUDED
#define VECTOR_TEMPLATE_H_INCLUDED

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <Vector>
#include <sstream>
#include <algorithm>
#include <chrono>
#include <cstring>
#include <stdexcept>
#include <cassert>
#include <utility>
#include <initializer_list>
#include <iterator>

template<typename T>
class Vector {
private:
    T* data;
    size_t _size;
    size_t _capacity;

    void reallocate(size_t newCapacity);

    template<typename InputIterator>
    void assign_impl(InputIterator first, InputIterator last, std::input_iterator_tag);

    template<typename RandomAccessIterator>
    void assign_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag);

public:
    Vector(size_t size, size_t capacity, const T& defaultValue)
    : _size(size), _capacity(capacity) {
    data = new T[_capacity];
    for (size_t i = 0; i < _size; ++i) {
        data[i] = defaultValue;
    }
}
    Vector();
    explicit Vector(size_t initialCapacity);
    Vector(size_t size, const T& defaultValue);
    Vector(std::initializer_list<T> initList);
    Vector(const Vector& other);
    Vector(Vector&& other) noexcept;
    Vector& operator=(const Vector& other);
    Vector& operator=(Vector&& other) noexcept;
    using value_type = T;
    ~Vector();

    void push_back(const T& value);
    void push_back(T&& value);
    void pop_back();
    size_t size() const;
    size_t capacity() const;
    bool empty() const;
    T& operator[](size_t index);
    const T& operator[](size_t index) const;
    void clear();
    void reserve(size_t newCapacity);
    T* begin();
    T* end();
    const T* begin() const;
    const T* end() const;
    T& back();
    const T& back() const;
    T& front();
    const T& front() const;
    T* data_ptr();
    const T* data_ptr() const;
    void erase(size_t index);
    void resize(size_t newSize, const T& defaultValue = T());
    void swap(Vector& other);

    template<typename InputIterator>
    void assign(InputIterator first, InputIterator last);
    void assign(size_t count, const T& value);
    void assign(std::initializer_list<T> ilist);

    void insert(size_t index, const T& value);
    template<typename InputIterator>
    void insert_range(size_t index, InputIterator first, InputIterator last);
    void append_range(std::initializer_list<T> ilist);

    T& at(size_t index);
    const T& at(size_t index) const;

    typename std::reverse_iterator<T*> rbegin();
    typename std::reverse_iterator<T*> rend();
    typename std::reverse_iterator<const T*> rbegin() const;
    typename std::reverse_iterator<const T*> rend() const;

    friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs) {
        if (lhs._size != rhs._size) {
            return false;
        }
        for (size_t i = 0; i < lhs._size; ++i) {
            if (lhs.data[i] != rhs.data[i]) {
                return false;
            }
        }
        return true;
    }

    friend bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(lhs == rhs);
    }

    friend bool operator<(const Vector<T>& lhs, const Vector<T>& rhs) {
        return std::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
    }

    friend bool operator<=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(rhs < lhs);
    }

    friend bool operator>(const Vector<T>& lhs, const Vector<T>& rhs) {
        return rhs < lhs;
    }

    friend bool operator>=(const Vector<T>& lhs, const Vector<T>& rhs) {
        return !(lhs < rhs);
    }
};

template<typename T>
Vector<T>::Vector() : data(nullptr), _size(0), _capacity(0) {}

template<typename T>
Vector<T>::Vector(size_t initialCapacity) : _size(0), _capacity(initialCapacity) {
    data = new T[_capacity];
}

template<typename T>
Vector<T>::Vector(size_t size, const T& defaultValue) : _size(size), _capacity(size) {
    data = new T[_capacity];
    std::fill(data, data + _size, defaultValue);
}

template<typename T>
Vector<T>::Vector(std::initializer_list<T> initList) : _size(initList.size()), _capacity(initList.size()) {
    data = new T[_capacity];
    std::copy(initList.begin(), initList.end(), data);
}

template<typename T>
Vector<T>::Vector(const Vector& other) : _size(other._size), _capacity(other._capacity) {
    data = new T[_capacity];
    std::copy(other.data, other.data + _size, data);
}

template<typename T>
Vector<T>::Vector(Vector&& other) noexcept : data(other.data), _size(other._size), _capacity(other._capacity) {
    other.data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if (this != &other) {
        T* newData = new T[other._capacity];
        std::copy(other.data, other.data + other._size, newData);
        delete[] data;
        data = newData;
        _size = other._size;
        _capacity = other._capacity;
    }
    return *this;
}

template<typename T>
Vector<T>& Vector<T>::operator=(Vector&& other) noexcept {
    if (this != &other) {
        delete[] data;
        data = other.data;
        _size = other._size;
        _capacity = other._capacity;
        other.data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

template<typename T>
Vector<T>::~Vector() {
    delete[] data;
}

template<typename T>
void Vector<T>::push_back(const T& value) {
    if (_size == _capacity) {
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    }
    data[_size++] = value;
}

template<typename T>
void Vector<T>::push_back(T&& value) {
    if (_size == _capacity) {
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    }
    data[_size++] = std::move(value);
}

template<typename T>
void Vector<T>::pop_back() {
    if (_size > 0) {
        --_size;
    }
}

template<typename T>
size_t Vector<T>::size() const {
    return _size;
}

template<typename T>
size_t Vector<T>::capacity() const {
    return _capacity;
}

template<typename T>
bool Vector<T>::empty() const {
    return _size == 0;
}

template<typename T>
T& Vector<T>::operator[](size_t index) {
    return data[index];
}

template<typename T>
const T& Vector<T>::operator[](size_t index) const {
    return data[index];
}

template<typename T>
void Vector<T>::clear() {
    _size = 0;
}

template<typename T>
void Vector<T>::reserve(size_t newCapacity) {
    if (newCapacity > _capacity) {
        reallocate(newCapacity);
    }
}

template<typename T>
T* Vector<T>::begin() {
    return data;
}

template<typename T>
T* Vector<T>::end() {
    return data + _size;
}

template<typename T>
const T* Vector<T>::begin() const {
    return data;
}

template<typename T>
const T* Vector<T>::end() const {
    return data + _size;
}

template<typename T>
T& Vector<T>::back() {
    if (_size == 0) {
        throw std::out_of_range("Kvieciamas back() tusciam vektoriui");
    }
    return data[_size - 1];
}

template<typename T>
const T& Vector<T>::back() const {
    if (_size == 0) {
        throw std::out_of_range("Kvieciamas back() tusciam vektoriui");
    }
    return data[_size - 1];
}

template<typename T>
T& Vector<T>::front() {
    if (_size == 0) {
        throw std::out_of_range("Kvieciamas front() tusciam vektoriui");
    }
    return data[0];
}

template<typename T>
const T& Vector<T>::front() const {
    if (_size == 0) {
        throw std::out_of_range("Kvieciamas front() tusciam vektoriui");
    }
    return data[0];
}

template<typename T>
T* Vector<T>::data_ptr() {
    return data;
}

template<typename T>
const T* Vector<T>::data_ptr() const {
    return data;
}

template<typename T>
void Vector<T>::erase(size_t index) {
    if (index < _size) {
        std::move(data + index + 1, data + _size, data + index);
        --_size;
    }
}

template<typename T>
void Vector<T>::resize(size_t newSize, const T& defaultValue) {
    if (newSize > _capacity) {
        reallocate(newSize);
    }
    if (newSize > _size) {
        std::fill(data + _size, data + newSize, defaultValue);
    }
    _size = newSize;
}

template<typename T>
void Vector<T>::swap(Vector& other) {
    std::swap(data, other.data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
}

template<typename T>
template<typename InputIterator>
void Vector<T>::assign(InputIterator first, InputIterator last) {
    using category = typename std::iterator_traits<InputIterator>::iterator_category;
    assign_impl(first, last, category());
}

template<typename T>
template<typename InputIterator>
void Vector<T>::assign_impl(InputIterator first, InputIterator last, std::input_iterator_tag) {
    clear();
    for (; first != last; ++first) {
        push_back(*first);
    }
}

template<typename T>
template<typename RandomAccessIterator>
void Vector<T>::assign_impl(RandomAccessIterator first, RandomAccessIterator last, std::random_access_iterator_tag) {
    size_t newSize = std::distance(first, last);
    if (newSize > _capacity) {
        reallocate(newSize);
    }
    std::copy(first, last, data);
    _size = newSize;
}

template<typename T>
void Vector<T>::assign(std::initializer_list<T> ilist) {
    size_t newSize = ilist.size();
    if (newSize > _capacity) {
        reallocate(newSize);
    }
    std::copy(ilist.begin(), ilist.end(), data);
    _size = newSize;
}

template<typename T>
void Vector<T>::assign(size_t count, const T& value) {
    size_t newSize = count;
    if (newSize > _capacity) {
        reallocate(newSize);
    }
    std::fill_n(data, count, value);
    _size = count;
}

template<typename T>
void Vector<T>::insert(size_t index, const T& value) {
    if (_size == _capacity) {
        reallocate(_capacity == 0 ? 1 : _capacity * 2);
    }
    if (index < _size) {
        std::move_backward(data + index, data + _size, data + _size + 1);
    }
    data[index] = value;
    ++_size;
}

template<typename T>
template<typename InputIterator>
void Vector<T>::insert_range(size_t index, InputIterator first, InputIterator last) {
    size_t count = std::distance(first, last);
    if (_size + count > _capacity) {
        reallocate(_size + count);
    }
    if (index < _size) {
        std::move_backward(data + index, data + _size, data + _size + count);
    }
    std::copy(first, last, data + index);
    _size += count;
}

template<typename T>
void Vector<T>::append_range(std::initializer_list<T> ilist) {
    if (_size + ilist.size() > _capacity) {
        reallocate(_size + ilist.size());
    }
    std::copy(ilist.begin(), ilist.end(), data + _size);
    _size += ilist.size();
}

template<typename T>
T& Vector<T>::at(size_t index) {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
const T& Vector<T>::at(size_t index) const {
    if (index >= _size) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template<typename T>
typename std::reverse_iterator<T*> Vector<T>::rbegin() {
    return std::reverse_iterator<T*>(end());
}

template<typename T>
typename std::reverse_iterator<T*> Vector<T>::rend() {
    return std::reverse_iterator<T*>(begin());
}

template<typename T>
typename std::reverse_iterator<const T*> Vector<T>::rbegin() const {
    return std::reverse_iterator<const T*>(end());
}

template<typename T>
typename std::reverse_iterator<const T*> Vector<T>::rend() const {
    return std::reverse_iterator<const T*>(begin());
}

template<typename T>
void Vector<T>::reallocate(size_t newCapacity) {
    T* newData = new T[newCapacity];
    if (data) {
        std::move(data, data + _size, newData);
        delete[] data;
    }
    data = newData;
    _capacity = newCapacity;
}


#endif // VECTOR_TEMPLATE_H_INCLUDED
