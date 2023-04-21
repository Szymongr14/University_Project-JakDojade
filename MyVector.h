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


    T& operator[](int index) const;
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;


private:
    void resize();
};


#endif //JAKDOAJDE_MYVECTOR_H
