//
// Created by szymo on 23.04.2023.
//

#ifndef INC_4_IN_MYPRIORITYQUEUE_H
#define INC_4_IN_MYPRIORITYQUEUE_H
#include "MyString.h"
#include <queue>

class Field{
public:
    int x;
    int y;
    int distance;
    MyString city;
    Field *next;
    Field *prev;

    Field(int x, int y, int distance, MyString city):x{x},y{y},distance{distance}, next{nullptr}, prev{nullptr}, city{std::move(city)}{}
    ~Field() = default;

//    Field& operator=(const Field& other) {
//        if (this != &other) {
//            x = other.x;
//            y = other.y;
//            distance = other.distance;
//            next = other.next;
//            prev = other.prev;
//        }
//        return *this;
//    }
};


struct CompareFieldDistance {
    bool operator()(const Field& a, const Field& b) {
        return a.distance > b.distance;
    }
};

class MyPriorityQueue {
private:
    std::priority_queue<Field, std::vector<Field>, CompareFieldDistance> pq;

public:
    MyPriorityQueue() {}
    ~MyPriorityQueue() = default;

    void push(const Field& element) {
        pq.push(element);
    }

    void pop() {
        pq.pop();
    }

    bool isEmpty() const {
        return pq.empty();
    }

    Field& front() const {
        return const_cast<Field &>(pq.top());
    }

//    Field* back() const {
//        // Since priority_queue doesn't provide direct access to its back element,
//        // we need to define our own function to traverse the queue and return the last element.
//        if (pq.empty()) {
//            return nullptr;
//        }
//        const auto& elements = pq.c;
//        return const_cast<Field*>(&elements[elements.size() - 1]);
//    }
};


#endif //INC_4_IN_MYPRIORITYQUEUE_H
