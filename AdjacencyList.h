//
// Created by szymo on 14.04.2023.
//

#ifndef JAKDOAJDE_ADJACENCYLIST_H
#define JAKDOAJDE_ADJACENCYLIST_H

#include <utility>

#include "MyVector.h"
#include "MyString.h"


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


class AdjacencyList {
private:
    MyVector <Vertex> vertices;
public:
    // Add a vertex to the list
    void addVertex(const Vertex& v) {
        vertices.pushBack(v);
    }

    // Add an edge to the list
    void addEdge(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);
        if (index >= 0) {
            vertices[index].addEdge(Edge(v, weight));
        }
    }

    // Get the index of the vertex with the given name
    int indexOfVertex(const MyString& name) {
        for (int i = 0; i < vertices.getSize(); i++) {
            if (vertices[i].name == name) {
                return i;
            }
        }
        return -1; // not found
    }

    // Print the adjacency list
    void printList() {
        for(int i = 0; i < vertices.getSize(); i++) {
            std::cout << vertices[i].name << ": ";
            vertices[i].edges.printList();
        }
    }

};


#endif //JAKDOAJDE_ADJACENCYLIST_H
