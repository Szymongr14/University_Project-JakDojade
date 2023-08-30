//
// Created by szymo on 14.04.2023.
//

#ifndef JAKDOAJDE_ADJACENCYLIST_H
#define JAKDOAJDE_ADJACENCYLIST_H

#include "MyVector.h"
#include "MyString.h"
#include "MyPriorityQueue.h"
#include <climits>


class Edge{
public:
    MyString name;
    int weight;
    Edge(MyString name, int weight):name{std::move(name)}, weight{weight}{}
    Edge():name{""}, weight{0}{}
};


class Vertex{
public:
    MyString name;
    MyVector<Edge> edges{32};

    Vertex(MyString name, MyVector<Edge> edges)
        :name{std::move(name)}, edges{std::move(edges)}{
    }
    Vertex()
        :name{""}{
    }

    void addEdge(const Edge& element){
        edges.pushBack(element);
    }

    void printEdges() const{
        for(int i=0; i<edges.getSize(); i++){
            std::cout << edges[i].name<<"|" <<edges[i].weight<< ", ";
        }
        std::cout << std::endl;
    }
};

class Pair {
public:
    unsigned int hash_value;
    int index;
    MyString name;
};

class AdjacencyList {
private:
    MyVector <Vertex> vertices;
    MyVector <MyVector<Pair>> hash_table{272139};
public:
    void addVertex(const Vertex& v) {
        vertices.pushBack(v);
        unsigned int hash_value = hash_string(v.name);
        hash_table[hash_value % hash_table.getCapacity()].pushBack(Pair{hash_value, vertices.getSize() - 1, v.name});
    }

    void addVertex(const MyString& name) {
        Vertex v{name, MyVector<Edge>{32}};
        vertices.pushBack(v);
        unsigned int hash_value = hash_string(name);
        hash_table[hash_value % hash_table.getCapacity()].pushBack(Pair{hash_value, vertices.getSize() - 1, name});
    }

    void addEdge(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);
        if (index >= 0) {
            vertices[index].addEdge(Edge(v, weight));
        }
    }

    void addFlight(const MyString& u, const MyString& v, int weight) {
        int index = indexOfVertex(u);
        if (index >= 0) {
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

    void printList() {
        for(int i = 0; i < vertices.getSize(); i++) {
            std::cout << vertices[i].name << ": ";
            vertices[i].printEdges();
        }
    }

    static unsigned int hash_string(const MyString& str) {
        const unsigned int FNV_offset_basis = 2166136261u;
        const unsigned int FNV_prime = 16777619u;

        unsigned int hash_value = FNV_offset_basis;
        int size = str.length();
        for (int i = 0; i < size; i++) {
            hash_value ^= (unsigned int) str[i];
            hash_value *= FNV_prime;
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
        MyPriorityQueue set;
        set.push(EdgePair{start, 0});
        MyVector<int> distances(vertices.getSize(), INT_MAX);
        MyVector<int> previous(vertices.getSize(), -1);
        distances[start_index] = 0;
        while(set.getSize()!=0){
            EdgePair temp = set.top();
            set.pop();
            int index = indexOfVertex(temp.name);
            for(int i=0; i<vertices[index].edges.getSize(); i++){
                Edge temp2 = vertices[index].edges[i];
                int index2 = indexOfVertex(temp2.name);
                if(distances[index2] > distances[index] + temp2.weight){
                    distances[index2] = distances[index] + temp2.weight;
                    previous[index2] = index;
                    EdgePair temp3{temp2.name, distances[index2]};
                    set.push(temp3);
                }
            }
        }
        if(mode == 0){
            std::cout<<distances[end_index]<<std::endl;
            return;
        }
        else{
            MyVector <MyString> path(200);
            int index = end_index;
            while(index != start_index){
                if(index!=end_index)path.pushBack(vertices[index].name);
                index = previous[index];
            }
            std::cout<<distances[end_index]<<" ";
            for(int i=path.getSize()-1; i>=0; i--){
                std::cout<<path[i]<<" ";
            }
            std::cout<<std::endl;
        }
    }
};


#endif //JAKDOAJDE_ADJACENCYLIST_H
