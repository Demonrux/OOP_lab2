#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <initializer_list>
#include <stdexcept>
#include "iterator.h"

template <typename Type>
class Vector {
private:
    Type* data;
    int capacity;
    int length;

    void resize(int newСapacity);

public:
    Vector(int length = 0);
    Vector(const Vector<Type>& vector);
    Vector(Vector<Type>&& vector) noexcept;
    Vector(std::initializer_list<Type> list);
    ~Vector();

    Vector<Type>& operator=(const Vector<Type>& list);
    Vector<Type>& operator=(Vector<Type>&& list) noexcept;

    bool isEmpty() const { return length == 0; }
    void swap(Vector<Type>& other) noexcept;
    void clear();
    void pushBack(const Type& value);
    void popBack();
    int size() const { return length; }
    void setElem(int index, const Type& elem);
    Type& getElem(int index);
    const Type& getElem(int index) const;
    Type* toArray() const;

    Type& operator[](int index);
    const Type& operator[](int index) const;

    Vector<Type>& operator+=(const Vector<Type>& vector);
    Vector<Type>& operator-=(const Vector<Type>& vector);
    Vector<Type>& operator*=(const Type& value);
    Vector<Type>& operator/=(const Type& value);

    Iterator<Type> begin() { return Iterator<Type>(*this, 0); }
    Iterator<Type> end() { return Iterator<Type>(*this, length); }

    template<typename U>
    friend std::ostream& operator<<(std::ostream& os, const Vector<U>& vector);
    template<typename U>
    friend Vector<U> operator+(const Vector<U>& vector1, const Vector<U>& vector2);

    template<typename U>
    friend Vector<U> operator-(const Vector<U>& vector1, const Vector<U>& vector2);

    template<typename U>
    friend Vector<U> operator*(const Vector<U>& vector1, const U& value);

    template<typename U>
    friend Vector<U> operator/(const Vector<U>& vector1, const U& value);
};

template<typename Type>
Vector<Type> operator+(const Vector<Type>& vector1, const Vector<Type>& vector2) {
    if (vector1.length != vector2.length) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    Vector<Type> result(vector1.length);
    for (int i = 0; i < vector1.length; ++i) {
        result.data[i] = vector1.data[i] + vector2.data[i];
    }
    return result;
}

template<typename Type>
Vector<Type> operator-(const Vector<Type>& vector1, const Vector<Type>& vector2) {
    if (vector1.length != vector2.length) {
        throw std::invalid_argument("Vectors must be of the same size");
    }
    Vector<Type> result(vector1.length);
    for (int i = 0; i < vector1.length; ++i) {
        result.data[i] = vector1.data[i] - vector2.data[i];
    }
    return result;
}

template<typename Type>
Vector<Type> operator*(const Vector<Type>& vector1, const Type& value) {
    Vector<Type> result(vector1.length);
    for (int i = 0; i < vector1.length; ++i) {
        result.data[i] = vector1.data[i] * value;
    }
    return result;
}

template<typename Type>
Vector<Type> operator/(const Vector<Type>& vector1, const Type& value) {
    if (value == 0) {
        throw std::invalid_argument("Division by zero");
    }
    Vector<Type> result(vector1.length);
    for (int i = 0; i < vector1.length; ++i) {
        result.data[i] = vector1.data[i] / value;
    }
    return result;
}

template<typename Type>
std::ostream& operator<<(std::ostream& os, const Vector<Type>& vector) {
    os << "[";
    for (int i = 0; i < vector.length; ++i) {
        if (i != 0) os << ", ";
        os << vector.data[i];
    }
    os << "]";
    return os;
}

template <typename Type>
void Vector<Type>::resize(int newCapacity) {
    Type* new_data = new Type[newCapacity];
    for (int i = 0; i < length; ++i) {
        new_data[i] = data[i];
    }
    delete[] data;
    data = new_data;
    capacity = newCapacity;
}

template <typename Type>
Vector<Type>::Vector(int length) : capacity(length > 0 ? length : 1), length(length) {
    data = new Type[capacity];
    for (int i = 0; i < length; ++i) {
        data[i] = Type();
    }
}

template <typename Type>
Vector<Type>::Vector(const Vector<Type>& vect) : capacity(vect.capacity), length(vect.length) {
    data = new Type[capacity];
    for (int i = 0; i < length; ++i) {
        data[i] = vect.data[i];
    }
}

template <typename Type>
Vector<Type>::Vector(Vector<Type>&& vect) noexcept : data(vect.data), capacity(vect.capacity), length(vect.length) {
    vect.data = nullptr;
    vect.capacity = 0;
    vect.length = 0;
}

template <typename Type>
Vector<Type>::Vector(std::initializer_list<Type> lst) : capacity(lst.size()), length(lst.size()) {
    data = new Type[capacity];
    int i = 0;
    for (const auto& item : lst) {
        data[i++] = item;
    }
}

template <typename Type>
Vector<Type>::~Vector() {
    delete[] data;
}

template <typename Type>
void Vector<Type>::pushBack(const Type& value) {
    if (length == capacity) {
        resize(capacity == 0 ? 1 : capacity * 2);
    }
    data[length++] = value;
}

template <typename Type>
void Vector<Type>::popBack() {
    if (length == 0) {
        throw std::out_of_range("Vector is empty");
    }
    --length;
}

template <typename Type>
void Vector<Type>::clear() {
    length = 0;
}

template <typename Type>
void Vector<Type>::swap(Vector<Type>& other) noexcept {
    std::swap(data, other.data);
    std::swap(capacity, other.capacity);
    std::swap(length, other.length);
}

template <typename Type>
Vector<Type>& Vector<Type>::operator=(const Vector<Type>& list) {
    if (this != &list) {
        delete[] data;
        capacity = list.capacity;
        length = list.length;
        data = new Type[capacity];
        for (int i = 0; i < length; ++i) {
            data[i] = list.data[i];
        }
    }
    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator=(Vector<Type>&& list) noexcept {
    if (this != &list) {
        delete[] data;
        data = list.data;
        capacity = list.capacity;
        length = list.length;
        list.data = nullptr;
        list.capacity = 0;
        list.length = 0;
    }
    return *this;
}

template <typename Type>
void Vector<Type>::setElem(int index, const Type& elem) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    data[index] = elem;
}

template <typename Type>
Type& Vector<Type>::getElem(int index) {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename Type>
const Type& Vector<Type>::getElem(int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename Type>
Type* Vector<Type>::toArray() const {
    Type* arr = new Type[length];
    for (int i = 0; i < length; ++i) {
        arr[i] = data[i];
    }
    return arr;
}

template <typename Type>
Type& Vector<Type>::operator[](int index) {
    return const_cast<Type&>(static_cast<const Vector<Type>*>(this)->operator[](index));
}

template <typename Type>
const Type& Vector<Type>::operator[](int index) const {
    if (index < 0 || index >= length) {
        throw std::out_of_range("Index out of range");
    }
    return data[index];
}

template <typename Type>
Vector<Type>& Vector<Type>::operator+=(const Vector<Type>& vect) {
    if (length != vect.length) {
        throw std::invalid_argument("Vectors must be of the same length");
    }
    for (int i = 0; i < length; ++i) {
        data[i] += vect.data[i];
    }
    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator-=(const Vector<Type>& vect) {
    if (length != vect.length) {
        throw std::invalid_argument("Vectors must be of the same length");
    }
    for (int i = 0; i < length; ++i) {
        data[i] -= vect.data[i];
    }
    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator*=(const Type& value) {
    for (int i = 0; i < length; ++i) {
        data[i] *= value;
    }
    return *this;
}

template <typename Type>
Vector<Type>& Vector<Type>::operator/=(const Type& value) {
    if (value == 0) {
        throw std::invalid_argument("Division by zero");
    }
    for (int i = 0; i < length; ++i) {
        data[i] /= value;
    }
    return *this;
}

#endif // VECTOR_H
