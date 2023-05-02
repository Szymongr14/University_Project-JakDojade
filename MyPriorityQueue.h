//
// Created by szymo on 24.04.2023.
//

#ifndef INC_4_IN_MYPRIORITYQUEUE_H
#define INC_4_IN_MYPRIORITYQUEUE_H


#include "MyVector.h"
#include "MyString.h"

struct EdgePair {
    MyString name;
    int weight{};
    EdgePair(const MyString& value, int priority) : name(value), weight(priority) {}
    EdgePair()= default;
};

class MyPriorityQueue {
private:
    MyVector<EdgePair> heap;

public:
    void push(const EdgePair& value) {
        heap.pushBack(value);
        int childIndex = heap.getSize() - 1;
        int parentIndex = (childIndex - 1) / 2;

        while (childIndex > 0 && heap[parentIndex].weight > heap[childIndex].weight) {
            swap(heap[childIndex], heap[parentIndex]);
            childIndex = parentIndex;
            parentIndex = (childIndex - 1) / 2;
        }
    }

    void pop() {
        if (heap.getSize() == 0) {
            return;
        }
        if (heap.getSize() == 1) {
            heap.popBack();
            return;
        }

        heap[0] = heap[heap.getSize() - 1];
        heap.popBack();
        int parentIndex = 0;

        while (true) {
            int leftChildIndex = 2 * parentIndex + 1;
            int rightChildIndex = 2 * parentIndex + 2;

            if (leftChildIndex >= heap.getSize()) {
                break;
            }
            int minIndex = parentIndex;

            if (heap[leftChildIndex].weight < heap[minIndex].weight) {
                minIndex = leftChildIndex;
            }

            if (rightChildIndex < heap.getSize() && heap[rightChildIndex].weight < heap[minIndex].weight) {
                minIndex = rightChildIndex;
            }

            if (minIndex == parentIndex) {
                break;
            }
            swap(heap[parentIndex], heap[minIndex]);
            parentIndex = minIndex;
        }
    }

    EdgePair& top() {
        return heap[0];
    }

    bool empty() {
        return heap.getSize() == 0;
    }

    int getSize() {
        return heap.getSize();
    }

    template <typename T>
    void swap(T& a, T& b) {
        T tmp = a;
        a = b;
        b = tmp;
    }
};


#endif //INC_4_IN_MYPRIORITYQUEUE_H
