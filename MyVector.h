//
// Created by szymo on 13.04.2023.
//

#ifndef JAKDOAJDE_MYVECTOR_H
#define JAKDOAJDE_MYVECTOR_H

template <typename T>


class MyVector {
private:
    T* arr;
    int capacity;
    int size;

public:
    MyVector();
    MyVector(int initialCapacity);
    MyVector(int initialCapacity, T value);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    ~MyVector() {delete[] arr;}


    int getSize() const {return size;}
    void pushBack(const T& element);
    void remove(const T& value);
    void removeGivenIndex(int i);
    bool valueExist(T value);
    int indexOfValue(T value);
    void clear();
    int getCapacity() const {return capacity;}
    void popBack() {
        if (size > 0) {
            size--;
        }
    }


    T& operator[](int index) const;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;


private:
    void resize();
};

template<typename T>
MyVector<T>::MyVector(int initialCapacity, T value) {
    arr = new T[initialCapacity];
    capacity = initialCapacity;
    size = initialCapacity;
    for (int i = 0; i < initialCapacity; i++) {
        arr[i] = value;
    }

}


#endif //JAKDOAJDE_MYVECTOR_H
