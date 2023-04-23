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
    //~Edge() = default;
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

    Edge * getHead() {return head;}

    Edge * returnSpecifiedNode(int index){
        Edge *temp = head;
        for(int i=0; i<index; i++){
            temp = temp->next;
        }
        return temp;
    }

    int numberOfEdges(){
        Edge *temp = head;
        int counter = 0;
        while(temp != nullptr){
            counter++;
            temp = temp->next;
        }
        return counter;
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

    bool valueExist(const MyString& value){
        Edge *temp = head;
        while(temp != nullptr){
            if(temp->name == value){
                return true;
            }
            temp = temp->next;
        }
        return false;
    }

    void removeGivenIndex(int index){
        Edge *temp = head;
        Edge *prev = nullptr;
        if(index < 0 || index >= numberOfEdges()){
            return;
        }
        if(index == 0){
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            if (head == nullptr) {
                tail = nullptr;
            }
            delete temp;
            return;
        }
        for(int i=0; i<index; i++){
            prev = temp;
            temp = temp->next;
        }
        prev->next = temp->next;
        if (temp->next != nullptr) {
            temp->next->prev = prev;
        }
        if (temp->next == nullptr) {
            tail = prev;
        }
        delete temp;
    }


    int indexOfEdge(const MyString& value){
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



    MyString getName() const {return name;}

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
    MyString name;
};

struct EdgePair {
    MyString name;
    int weight;
};


class AdjacencyList {
private:
    MyVector <Vertex> vertices;
    MyVector <MyVector<Pair>> hash_table{2000};
public:
    // Add a vertex to the list
    void addVertex(const Vertex& v) {
        vertices.pushBack(v);
        unsigned int hash_value = hash_string(v.name);
        hash_table[hash_value % hash_table.getCapacity()].pushBack(Pair{hash_value, vertices.getSize() - 1, v.name});
    }

    void addVertex(const MyString& name) {
        Vertex v{name, LinkedList()};
        vertices.pushBack(v);
        unsigned int hash_value = hash_string(name);
        hash_table[hash_value % hash_table.getCapacity()].pushBack(Pair{hash_value, vertices.getSize() - 1, name});
    }

    // Add an edge to the list
    void addEdge(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);
        if (index >= 0) {
            vertices[index].addEdge(Edge(v, weight));
        }
    }

    void addFlight(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);


        if (index >= 0) {
//            if(vertices[index].edges.valueExist(v)){
//                int index2 = vertices[index].edges.indexOfEdge(v);
//                if(vertices[index].edges.returnSpecifiedNode(index2)->weight > weight){
//                    vertices[index].edges.removeGivenIndex(index2);
//                    this->addEdge(u, v, weight);
//                }
//            }
            this->addEdge(u, v, weight);

        }
    }

    int indexOfVertex(const MyString& name) {
        unsigned int hash_value = hash_string(name);
        MyVector<Pair> &temp = hash_table[hash_value % hash_table.getCapacity()];
        for (int i = 0; i < temp.getSize(); i++) {
            if (temp[i].name == name) {
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


    void findShortestPath(const MyString& start, const MyString& end, int mode){
        int start_index = indexOfVertex(start);
        int end_index = indexOfVertex(end);
        if(start_index == -1 || end_index == -1){
            //std::cout << "No such vertex" << std::endl;
            return;
        }
        MyVector<EdgePair> set;
        set.pushBack(EdgePair{start, 0});
        MyVector<int> distances(vertices.getSize(), INT_MAX);
        MyVector<int> previous(vertices.getSize(), -1);
        distances[start_index] = 0;

        while(set.getSize()!=0){
            EdgePair temp = set[0];
            set.removeGivenIndex(0);
            int index = indexOfVertex(temp.name);
            for(int i=0; i<vertices[index].edges.numberOfEdges(); i++){
                Edge *temp2 = vertices[index].edges.returnSpecifiedNode(i);
                int index2 = indexOfVertex(temp2->name);
                if(distances[index2] > distances[index] + temp2->weight){
                    distances[index2] = distances[index] + temp2->weight;
                    previous[index2] = index;
                    EdgePair temp3{temp2->name, distances[index2]};
                    set.pushBack(temp3);
                }
            }
        }
        if(mode == 0){
            //std::cout<<"Shortest path from "<<start<<" to "<<end<<" is: "<<distances[end_index]<<std::endl;
            std::cout<<distances[end_index]<<std::endl;
            return;
        }
        else{
            MyVector <MyString> path(100);
            int index = end_index;
            while(index != start_index){
                if(index!=end_index)path.pushBack(vertices[index].name);
                index = previous[index];
            }
            //std::cout<<"Shortest path from "<<start<<" to "<<end<<" is: "<<distances[end_index]<<std::endl;
            std::cout<<distances[end_index]<<" ";
            for(int i=path.getSize()-1; i>=0; i--){
                std::cout<<path[i]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};


#endif //JAKDOAJDE_ADJACENCYLIST_H
