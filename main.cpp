#include <iostream>
#include "MyVector.hxx"
#include "MyString.h"
#include "AdjacencyList.h"
#include "MyQueue.h"
#include <time.h>
#include "Board.h"

void findNeighbours(const Board& board,long int i, long int j, const MyString& cityName, AdjacencyList& adjList){
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
    clock_t startTime = clock(); // start pomiaru czasu
    AdjacencyList adjList;
    MyString cityName = "";

    for(int i=0; i<board.cities.getSize(); i++) {
        cityName = board.findCityName(board.cities[i].x, board.cities[i].y);
        findNeighbours(board,board.cities[i].x, board.cities[i].y, cityName, adjList);
    }
    return adjList;
}


int main() {
    clock_t startTime1, endTime1;
    double time_taken1;
    startTime1 = clock(); // start pomiaru czasu

    int height=0, width=0, queries=0,flights=0;
    AdjacencyList adjList;
    char c;
    std::cin >> width >> height;
    Board board{height,width};

    clock_t startTime2=clock(), endTime2;
    double time_taken2;
    board.laodBoard();
    endTime2 = clock(); // koniec pomiaru czasu
    time_taken2 = (double)(endTime2 - startTime2) / CLOCKS_PER_SEC;
    //std::cout << "czas wczytywania: " << time_taken2 << std::endl;


//    std::cout << "Array elements: " << std::endl;
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            std::cout << board[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    clock_t startTime3=clock(), endTime3;
    double time_taken3;
    adjList = createGraph(board);
    endTime3 = clock(); // koniec pomiaru czasu
    time_taken3 = (double)(endTime3 - startTime3) / CLOCKS_PER_SEC;
    //std::cout << "czas tworzenia grafu: " << time_taken3 << std::endl;


    clock_t startTime4=clock(), endTime4;
    double time_taken4;
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
        //std::cout<<startCity<<" "<<endCity<<" "<<distanceStr<<std::endl;
        adjList.addFlight(startCity,endCity,MyString::stringToInt(distanceStr));
    }
    endTime4 = clock(); // koniec pomiaru czasu
    time_taken4 = (double)(endTime4 - startTime4) / CLOCKS_PER_SEC;
    //std::cout << "czas wczytywania lotow: " << time_taken4 << std::endl;

    //adjList.printList();


    clock_t startTime5=clock(), endTime5;
    double time_taken5;
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
    endTime5 = clock(); // koniec pomiaru czasu
    time_taken5 = (double)(endTime5 - startTime5) / CLOCKS_PER_SEC;
    //std::cout << "czas disjktry: " << time_taken5 << std::endl;

    endTime1 = clock(); // koniec pomiaru czasu
    time_taken1 = double(endTime1 - startTime1) / double(CLOCKS_PER_SEC); // obliczenie czasu trwania

    //std::cout << "Compilation time: " << time_taken1 << " s" << std::endl;
    return 0;
}
