//
// Created by szymo on 14.04.2023.
//

#ifndef JAKDOAJDE_ADJACENCYLIST_H
#define JAKDOAJDE_ADJACENCYLIST_H

#include <utility>

#include "MyVector.h"
#include "MyString.h"

#include <math.h>

class Edge{
public:
    MyString name;
    int weight;
    Edge *next;
    Edge *prev;

    Edge(MyString name, int weight):name{std::move(name)}, weight{weight}, next{nullptr}, prev{nullptr}{}
    ~Edge() = default;
    MyString getName() const {return name;}
};

class LinkedList {
private:
    Edge *head;
    Edge *tail;
public:
    LinkedList():head{nullptr}, tail{nullptr}{}
    ~LinkedList() = default;

    void addNode(const Edge& element){
        Edge *newNode = new Edge{element.name, element.weight};
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
    void remove(const Edge& value){
        Edge *temp = head;
        Edge *prev = nullptr;
        if(head == nullptr){
            return;
        }
        if(head->name == value.name){
            head = head->next;
            delete temp;
            return;
        }
        while(temp != nullptr && !(temp->name == value.name)){
            prev = temp;
            temp = temp->next;
        }
        if(temp == nullptr){
            return;
        }
        prev->next = temp->next;
        delete temp;
    }
    void removeGivenIndex(int i){
        Edge *temp = head;
        Edge *prev = nullptr;
        if(head == nullptr){
            return;
        }
        if(i == 0){
            head = head->next;
            delete temp;
            return;
        }
        int index = 0;
        while(temp != nullptr && index != i){
            prev = temp;
            temp = temp->next;
            index++;
        }
        if(temp == nullptr){
            return;
        }
        prev->next = temp->next;
        delete temp;
    }
    bool valueExist(const Edge& value){
        Edge *temp = head;
        while(temp != nullptr){
            if(temp->name == value.name){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    int indexOfVertex(const MyString& value){
        Edge *temp = head;
        int index = 0;
        while(temp != nullptr){
            if(temp->name == value){
                return index;
            }
            temp = temp->next;
            index++;
        }
        return -1;
    }

    void printList(){
        Edge *temp = head;
        while(temp != nullptr){
            std::cout << temp->name<<"|" <<temp->weight<< ", ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};


class Vertex{
public:
    MyString name;
    LinkedList edges;

    Vertex(MyString name, LinkedList edges)
        :name{std::move(name)}, edges{edges}{

    }
    Vertex()
        :name{""}{
    }

    ~Vertex() = default;

    MyString getName() const {return name;}
    LinkedList getEdges() const {return edges;}

    void addEdge(const Edge& element){
        edges.addNode(element);
    }

    void printEdges(){
        edges.printList();
    }
};

class Pair {
public:
    unsigned int hash_value;
    int index;
};


class AdjacencyList {
private:
    MyVector <Vertex> vertices;
    MyVector <MyVector<Pair>> hash_table{999};
public:
    // Add a vertex to the list
    void addVertex(const Vertex& v) {
        vertices.pushBack(v);
        unsigned int hash_value = hash_string(v.name);
        hash_table[hash_value % hash_table.getCapacity()].pushBack(Pair{hash_value, vertices.getSize() - 1});
    }

    // Add an edge to the list
    void addEdge(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);
        if (index >= 0) {
            vertices[index].addEdge(Edge(v, weight));
        }
    }

    int indexOfVertex(const MyString& name) {
        unsigned int hash_value = hash_string(name);
        MyVector<Pair> &temp = hash_table[hash_value % hash_table.getCapacity()];
        for (int i = 0; i < temp.getSize(); i++) {
            if (temp[i].hash_value == hash_value) {
                return temp[i].index;
            }
        }
        return -1;
    }

//    // Get the index of the vertex with the given name
//    int indexOfVertex(const MyString& name) {
//        for (int i = 0; i < vertices.getSize(); i++) {
//            if (vertices[i].name == name) {
//                return i;
//            }
//        }
//        return -1; // not found
//    }


    void printList() {
        for(int i = 0; i < vertices.getSize(); i++) {
            std::cout << vertices[i].name << ": ";
            vertices[i].edges.printList();
        }
    }

    static unsigned int hash_string(const MyString& str) {
        unsigned int hash_value = 0;
        int size = str.length();
        for(int i = 0; i < size; i++)  {
            unsigned int temp = (int)str[i] % (int)(pow(2, 32));
            hash_value = hash_value * 31 + temp;
        }
        return hash_value;
    }
};


#endif //JAKDOAJDE_ADJACENCYLIST_H
