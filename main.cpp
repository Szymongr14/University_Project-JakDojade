#include <iostream>
#include "MyVector.hxx"
#include "MyString.h"
#include "AdjacencyList.h"
#include "MyQueue.h"
#include <time.h>
#include "Board.h"

void findNeighbours(const Board& board,int i,int j, const MyString& cityName, AdjacencyList& adjList){
    MyQueue queue;
    MyString neighbourName = "";
    bool needToRestoreVisited = false;
    adjList.addVertex(cityName);

    Field start(i,j,0);
    queue.push(start);
    while(!queue.empty()){
        Field &first = queue.top();
        i = first.x;
        j = first.y;
        if(board.getIndex(i,j) == '*' && first.weight != 0){
            neighbourName = board.findCityName(i,j);
            adjList.addEdge(cityName,neighbourName,first.weight);
            queue.pop();
            continue;
        }
        if(board.isInBoard(i+1,j) && (board.getIndex(i+1,j) == '*' || (board.getIndex(i+1,j) == '#')) && !board.isVisited(i+1,j)){
            Field next(i+1,j,first.weight+1);
            queue.push(next);
            board.setVisited(i+1,j);
            needToRestoreVisited = true;
        }

        if(board.isInBoard(i,j+1) && ((board.getIndex(i,j+1) == '*' || board.getIndex(i,j+1) == '#')) && !board.isVisited(i,j+1)){
            Field next(i,j+1,first.weight+1);
            queue.push(next);
            board.setVisited(i,j+1);
            needToRestoreVisited = true;
        }

        if(board.isInBoard(i,j-1) && ((board.getIndex(i,j-1) == '*' || board.getIndex(i,j-1) == '#')) && !board.isVisited(i,j-1)){
            Field next(i,j-1,first.weight+1);
            queue.push(next);
            board.setVisited(i,j-1);
            needToRestoreVisited = true;
        }

        if(board.isInBoard(i-1,j) && (board.getIndex(i-1,j) == '*' || board.getIndex(i-1,j) == '#') && !board.isVisited(i-1,j)){
            Field next(i-1,j,first.weight+1);
            queue.push(next);
            board.setVisited(i-1,j);
            needToRestoreVisited = true;
        }
        queue.pop();
    }
    if(needToRestoreVisited) board.restoreVisited();
}

AdjacencyList createGraph(const Board& board) {
    AdjacencyList adjList;
    MyString cityName = "";

    for(int i=0; i<board.cities.getSize(); i++) {
        cityName = board.findCityName(board.cities[i].x, board.cities[i].y);
        findNeighbours(board,board.cities[i].x, board.cities[i].y, cityName, adjList);
    }
    return adjList;
}


int main() {
    int height=0, width=0, queries=0,flights=0;
    AdjacencyList adjList;
    char c;

    std::cin >> width >> height;
    Board board{height,width};

    board.laodBoard();

    adjList = createGraph(board);

    std::cin>>flights;
    getchar();
    MyString line;
    for(int i = 0; i < flights; i++){
        MyVector<char> start, end, distance;
        int order=0;
        std::cin >> line;
        for(int j = 0; j < line.length(); j++){
            if(line[j]==' '){
                order++;
                continue;
            }
            if(order==0) start.pushBack(line[j]);
            if(order==1) end.pushBack(line[j]);
            if(order==2) distance.pushBack(line[j]);
        }
        start.pushBack('\0');
        end.pushBack('\0');
        distance.pushBack('\0');
        MyString startCity(MyString::fromCharVector(start));
        MyString endCity(MyString::fromCharVector(end));
        MyString distanceStr(MyString::fromCharVector(distance));
        adjList.addFlight(startCity,endCity,MyString::stringToInt(distanceStr));
    }
    //adjList.printList();

    std::cin>>queries;
    getchar();
    for(int i = 0; i < queries; i++){
        MyVector<char> start, end, mode;
        int order=0;
        std::cin >> line;
        for(int j = 0; j < line.length(); j++){
            if(line[j]==' '){
                order++;
                continue;
            }
            if(order==0) start.pushBack(line[j]);
            if(order==1) end.pushBack(line[j]);
            if(order==2) mode.pushBack(line[j]);
        }
        start.pushBack('\0');
        end.pushBack('\0');
        mode.pushBack('\0');
        MyString startCity(MyString::fromCharVector(start));
        MyString endCity(MyString::fromCharVector(end));
        MyString modeStr(MyString::fromCharVector(mode));
        adjList.findShortestPath(startCity,endCity,MyString::stringToInt(modeStr));
    }
    return 0;
}
