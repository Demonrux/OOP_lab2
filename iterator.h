#ifndef ITERATOR_H
#define ITERATOR_H

#include <iostream>

template <typename Type>
class Vector;

template <typename Type>
class Iterator {
private:
    Vector<Type>& container;
    int index;

public:
    Iterator(Vector<Type>& containerObj, int startIndex = 0);
    Iterator<Type> next();
    Type& value();
    bool isEnd() const;

    Iterator<Type>& operator++();
    Iterator<Type> operator++(int);
    Type& operator*();
    bool operator==(const Iterator<Type>& b) const;
    bool operator!=(const Iterator<Type>& b) const;
};

template <typename Type>
Iterator<Type>::Iterator(Vector<Type>& containerObj, int startIndex)
    : container(containerObj), index(startIndex) {}

template <typename Type>
Iterator<Type> Iterator<Type>::next() {
    if (index < container.size()) {
        index++;
    }
    return *this;
}

template <typename Type>
Type& Iterator<Type>::value() {
    if (index >= container.size()) {
        throw std::out_of_range("Iterator out of range");
    }
    return container[index] ;
}

template <typename Type>
bool Iterator<Type>::isEnd() const {
    return index >= container.size();
}

template <typename Type>
Iterator<Type>& Iterator<Type>::operator++() {
    next();
    return *this;
}

template <typename Type>
Iterator<Type> Iterator<Type>::operator++(int) {
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename Type>
Type& Iterator<Type>::operator*() {
    return value();
}

template <typename Type>
bool Iterator<Type>::operator==(const Iterator<Type>& b) const {
    return &container == &b.container && index == b.index;
}

template <typename Type>
bool Iterator<Type>::operator!=(const Iterator<Type>& b) const {
    return !(*this == b);
}

#endif // ITERATOR_H
