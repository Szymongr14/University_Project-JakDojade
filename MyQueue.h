//
// Created by szymo on 21.04.2023.
//

#ifndef JAKDOJADE_MYQUEUE_H
#define JAKDOJADE_MYQUEUE_H

class Field{
public:
    int x;
    int y;
    int distance;
    Field *next;
    Field *prev;

    Field(int x, int y, int distance):x{x},y{y},distance{distance}, next{nullptr}, prev{nullptr}{}
    ~Field() = default;

    Field& operator=(const Field& other) {
        if (this != &other) {
            x = other.x;
            y = other.y;
            distance = other.distance;
            next = other.next;
            prev = other.prev;
        }
        return *this;
    }
};


class MyQueue{
private:
    Field *head;
    Field *tail;
public:
    MyQueue():head{nullptr}, tail{nullptr}{}
    ~MyQueue() = default;

    void push(const Field& element){
        Field *newNode = new Field{element.x, element.y, element.distance};
        if(head == nullptr){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop(){
        Field *temp = head;
        if(head == nullptr){
            return;
        }
        if(head->next == nullptr){
            head = nullptr;
            tail = nullptr;
            delete temp;
            return;
        }
        head = head->next;
        head->prev = nullptr;
        delete temp;
    }



    bool isEmpty() const {return head == nullptr;}

    Field* front() const {return head;}
    Field* back() const {return tail;}
};


#endif //JAKDOJADE_MYQUEUE_H
