#include "MyVector.h"
#include "iostream"
template <typename T>
MyVector<T>::MyVector() : arr(nullptr), capacity(0), size(0) {}

template <typename T>
MyVector<T>::MyVector(int initialCapacity) : arr(new T[initialCapacity]), capacity(initialCapacity), size(0) {}

template <typename T>
MyVector<T>::MyVector(const MyVector<T>& other) : arr(new T[other.capacity]), capacity(other.capacity), size(other.size) {
    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}

template <typename T>
MyVector<T>::MyVector(MyVector<T>&& other) noexcept : arr(other.arr), capacity(other.capacity), size(other.size) {
    other.arr = nullptr;
    other.capacity = 0;
    other.size = 0;
}

template<typename T>
MyVector<T>::MyVector(int initialCapacity, T value) {
    arr = new T[initialCapacity];
    capacity = initialCapacity;
    size = initialCapacity;
    for (int i = 0; i < initialCapacity; i++) {
        arr[i] = value;
    }
}

template <typename T>
void MyVector<T>::pushBack(const T& element) {
    if (size >= capacity) {
        resize();
    }
    arr[size++] = element;
}

template <typename T>
T& MyVector<T>::operator[](int index) const{
    if (index < 0 || index >= capacity) {
        //throw std::out_of_range("Index out of range");
    }
    return arr[index];
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this != &other) {
        delete[] arr;
        arr = new T[other.capacity];
        capacity = other.capacity;
        size = other.size;
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

template <typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        capacity = other.capacity;
        size = other.size;
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

template <typename T>
void MyVector<T>::remove(const T& value) {
    int index = 0;
    while (index < size) {
        if (arr[index] == value) {
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
        else {
            index++;
        }
    }
}

template <typename T>
void MyVector<T>::removeGivenIndex(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (int j = i; j < size - 1; j++) {
        arr[j] = arr[j + 1];
    }
    size--;
}

template <typename T>
bool MyVector<T>::valueExist(T value) {
    for (int i = 0; i < this->getSize(); i++) {
        if (this->arr[i] == value) return true;
    }
    return false;
}

template <typename T>
int MyVector<T>::indexOfValue(T value) {
    for (int i = 0; i < this->getSize(); i++) {
        if (this->arr[i] == value) return i;
    }
    return 1;
}

template <typename T>
void MyVector<T>::resize() {
    if (capacity == 0) {
        capacity = 1;
        arr = new T[capacity];
    }
    else {
        capacity *= 2;
        T* newArr = new T[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
}

template <typename T>
void MyVector<T>::clear() {
    delete[] arr;
    arr = new T[capacity];
    size = 0;
}
