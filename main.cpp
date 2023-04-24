#include <iostream>
#include "MyVector.hxx"
#include "MyString.h"
#include "AdjacencyList.h"
#include "MyQueue.h"
#include <time.h>
//#include "MyPriorityQueue.h"

bool isInBoard(int i, int j, int height, int width){
    return i >= 0 && i < height && j >= 0 && j < width;
}
MyString checkTop(const char** arr, int height, int width, int i, int j){
    MyString name = "";

    if(i-1 >= 0 && arr[i-1][j] != '.' && arr[i-1][j] != '#' && arr[i-1][j]!= ' '){
        if(j> 0 && arr[i-1][j-1] == '.' || arr[i-1][j-1] == '#' || arr[i-1][j-1] == ' '){
                while(j < width &&arr[i-1][j] != '#' && arr[i-1][j] != '.' && arr[i-1][j] != ' '){
                    name += arr[i-1][j];
                    j++;
                }
        }
        else if(j==0){
            while(j < width &&arr[i-1][j] != '#' && arr[i-1][j] != '.' && arr[i-1][j] != ' '){
                name += arr[i-1][j];
                j++;
            }
        }
        else{
            if(j<width && MyString::isLetter(arr[i-1][j+1])) return "";
            while(arr[i-1][j] != '#' && arr[i-1][j] != '.' && arr[i-1][j] != ' '){
                name += arr[i-1][j];
                j--;
            }
            name.reverse();
        }
    }
    return name;
}

MyString checkBottom(const char** arr, int height, int width, int i, int j){
    MyString name = "";
    if(i+1 < height && arr[i+1][j] != '.' && arr[i+1][j] != '#' && arr[i+1][j] != ' '){
        if(j> 0 && (arr[i+1][j-1] == '.' || arr[i+1][j-1] == '#' || arr[i+1][j-1] == ' ')){
            while(j < width && arr[i+1][j] != '#' && arr[i+1][j] != '.' && arr[i+1][j] != ' '){
                name += arr[i+1][j];
                j++;
            }
        }
        else if(j==0){
            while(j < width && arr[i+1][j] != '#' && arr[i+1][j] != '.' && arr[i+1][j] != ' '){
                name += arr[i+1][j];
                j++;
            }
        }
        else if(j==width-1){
            while(j >= 0 && arr[i+1][j] != '#' && arr[i+1][j] != '.' && arr[i+1][j] != ' '){
                name += arr[i+1][j];
                j--;
            }
            name.reverse();
        }
        else{
            if(j<width && MyString::isLetter(arr[i+1][j+1])) return "";
            while(arr[i+1][j] != '#' && arr[i+1][j] != '.' && arr[i+1][j] != ' '){
                name += arr[i+1][j];
                j--;
            }
            name.reverse();
        }
    }
    return name;
}

MyString checkRightBottomCorner(const char ** arr, int height, int width, int i, int j){
    MyString name = "";
    if((i+1 < height&&j+1 < width) &&arr[i+1][j+1] != '.' && arr[i+1][j+1] != '#' && arr[i+1][j+1] != ' '){
        if(arr[i+1][j] == '.' || arr[i+1][j] == '#' || arr[i+1][j] == ' '){
            while(arr[i+1][j+1] != '#' && arr[i+1][j+1] != '.' && arr[i+1][j+1] != '*' && arr[i+1][j+1] != ' '){
                name += arr[i+1][j+1];
                j++;
            }
        }
        else{
            if(isInBoard(i+1,j+2,height,width) && isInBoard(i+1,j-1,height,width)&& MyString::isLetter(arr[i+1][j+2]) && MyString::isLetter(arr[i+1][j-1])) return "";
            while(arr[i+1][j+1] != '#' && arr[i+1][j+1] != '.' && arr[i+1][j+1] != '*' && arr[i+1][j+1] != ' '){
                name += arr[i+1][j+1];
                j--;
            }
            name.reverse();
        }
    }
    return name;
}

MyString checkLeftBottom(const char** arr, int height, int width, int i, int j){
    MyString name = "";
    if((i+1 < height&&j-1 >= 0) &&arr[i+1][j-1] != '.' && arr[i+1][j-1] != '#' && arr[i+1][j-1] != ' '){
        if(arr[i+1][j] == '.' || arr[i+1][j] == '#' || arr[i+1][j] == ' '){

            while(arr[i+1][j-1] != '#' && arr[i+1][j-1] != '.' && arr[i+1][j-1] != '*' && arr[i+1][j-1] != ' '){
                name += arr[i+1][j-1];
                j--;
            }
            name.reverse();
        }
        else{
            if(isInBoard(i+1,j+1,height,width)&& isInBoard(i+1,j-2,height,width) && MyString::isLetter(arr[i+1][j-2]) && MyString::isLetter(arr[i+1][j+1])) return "";
            while(arr[i+1][j-1] != '#' && arr[i+1][j-1] != '.' && arr[i+1][j-1] != '*' && arr[i+1][j-1] != ' '){
                name += arr[i+1][j-1];
                j++;
            }
        }
    }
    return name;
}

MyString checkRightTopCorner(const char** arr, int height, int width, int i, int j){
    MyString name = "";
    if((i-1 >= 0&&j+1 < width) && arr[i-1][j+1] != '.' && arr[i-1][j+1] != '#' && arr[i-1][j+1] != '*'){
        if(arr[i-1][j] == '.' || arr[i-1][j] == '#' || arr[i-1][j] == '*' || arr[i-1][j] == ' '){
            while(arr[i-1][j+1] != '#' && arr[i-1][j+1] != '.' && arr[i-1][j+1] != '*' && arr[i-1][j+1] != ' '){
                name += arr[i-1][j+1];
                j++;
            }
        }
        else{
            if(j<width && MyString::isLetter(arr[i-1][j+2])) return "";
            while(arr[i-1][j+1] != '#' && arr[i-1][j+1] != '.' && arr[i-1][j+1] != '*' && arr[i-1][j+1] != ' '){
                name += arr[i-1][j+1];
                j--;
            }
            name.reverse();
        }
    }
    return name;
}

MyString checkLeftTopCorner(const char** arr, int height, int width, int i, int j){
    MyString name = "";
    if((i-1 >= 0 && j-1 < width) && arr[i-1][j-1] != '.' && arr[i-1][j-1] != '#' && arr[i-1][j-1] != ' '){
        if(arr[i-1][j] == '.' || arr[i-1][j] == '#' || arr[i-1][j] == ' '){
            while(arr[i-1][j-1] != '#' && arr[i-1][j-1] != '.' && arr[i-1][j-1] != '*' && arr[i-1][j-1] != ' '){
                name += arr[i-1][j-1];
                j--;
            }
            name.reverse();
        }
        else{
            while(arr[i-1][j-1] != '#' && arr[i-1][j-1] != '.' && arr[i-1][j-1] != '*' && j!=width+1 && arr[i-1][j-1] != ' '){
                name += arr[i-1][j-1];
                j++;
            }
        }
    }
    return name;
}


MyString findCityName(const char** arr, int height, int width, int i, int j){
    MyString name ="";
    //top
    if(name == "") name = checkTop(arr,height,width,i,j);

    //bottom
    if(name == "")name = checkBottom(arr,height,width,i,j);

    //right
    if(name == ""){
        if(j+1 < width  && arr[i][j+1] != '.' && arr[i][j+1] != '#' && arr[i][j+1] != ' '){
            while(j+1 < width && arr[i][j+1] != '#' && arr[i][j+1] != '.' && arr[i][j+1] != '*' && arr[i][j+1] != ' '){
                name += arr[i][j+1];
                j++;
            }
        }
    }

    //left
    if(name == ""){
        if((j-1 >= 0) && arr[i][j-1] != '.' && arr[i][j-1] != '#' && arr[i][j-1] != ' '){
            while(arr[i][j-1] != '#' && arr[i][j-1] != '.' && arr[i][j-1] != '*' && arr[i][j-1] != ' '){
                name += arr[i][j-1];
                j--;
            }
            name.reverse();
        }
    }
    //right bottom corner
    if(name == "")name = checkRightBottomCorner(arr,height,width,i,j);

    //left bottom corner
    if(name == "")name = checkLeftBottom(arr,height,width,i,j);

    //right top corner
    if(name == "")name = checkRightTopCorner(arr,height,width,i,j);

    //left top corner
    if(name == "")name = checkLeftTopCorner(arr,height,width,i,j);
    return name;
}


void findNeighbours(const char** arr, int height, int width, int i, int j, const MyString& cityName, AdjacencyList& adjList){
    MyQueue queue;
    MyString neighbourName = "";
    adjList.addVertex(cityName);
    bool** visited = new bool*[height];
    for(int k=0; k<height; k++){
        visited[k] = new bool[width];
        for(int l=0; l<width; l++){
            visited[k][l] = false;
        }
    }

    Field start(i,j,0);
    queue.push(start);
    clock_t startTime = clock(); // start pomiaru czasu
    while(!queue.isEmpty()){
        Field &first = queue.front();
        i = first.x;
        j = first.y;
        if(arr[i][j] == '*' && first.distance != 0){
            neighbourName = findCityName((const char**) arr,height,width,i,j);
            adjList.addEdge(cityName,neighbourName,first.distance);
            queue.pop();
            continue;
        }
        if(isInBoard(i+1,j,height,width) && (arr[i+1][j] == '*' || arr[i+1][j] == '#') && !visited[i+1][j]){
            Field next(i+1,j,first.distance+1);
            queue.push(next);
            visited[i+1][j] = true;
        }

        if(isInBoard(i,j+1,height,width) && (arr[i][j+1] == '*' || arr[i][j+1] == '#') && !visited[i][j+1]){
            Field next(i,j+1,first.distance+1);
            queue.push(next);
            visited[i][j+1] = true;
        }

        if(isInBoard(i,j-1,height,width) && (arr[i][j-1] == '*' || arr[i][j-1] == '#') && !visited[i][j-1]){
            Field next(i,j-1,first.distance+1);
            queue.push(next);
            visited[i][j-1] = true;
        }

        if(isInBoard(i-1,j,height,width) && (arr[i-1][j] == '*' || arr[i-1][j] == '#') && !visited[i-1][j]){
            Field next(i-1,j,first.distance+1);
            queue.push(next);
            visited[i-1][j] = true;
        }

        queue.pop();
    }

    for(int k=0;k<height;k++){
        delete[] visited[k];
    }
    delete[] visited;

    clock_t endTime = clock(); // koniec pomiaru czasu
    double time = (double)(endTime - startTime) / CLOCKS_PER_SEC;
    //std::cout << "czas while: " << time << std::endl;
}

AdjacencyList parseArray(const char** arr, int height, int width) {
    clock_t startTime = clock(); // start pomiaru czasu
    AdjacencyList adjList;
    MyString cityName = "";
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] != '.' && !MyString::isLetter(arr[i][j])) {
                if(arr[i][j] == '*'){
                    cityName = findCityName(arr, height, width, i, j);
                    findNeighbours(arr, height, width, i, j, cityName, adjList);
                }
            }
        }
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

    char** board = new char*[height];

    for(int i = 0; i < height; i++){
        board[i] = new char[width];
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            c = getchar();
            while (c == '\n') {
                c = getchar();
            }
            board[i][j] = c;
        }
    }


//    std::cout << "Array elements: " << std::endl;
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            std::cout << board[i][j] << " ";
//        }
//        std::cout << std::endl;
//    }

    adjList = parseArray((const char**)board, height, width);

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

    // zwolnienie zaalokowanej pamięci
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;

    endTime1 = clock(); // koniec pomiaru czasu
    time_taken1 = double(endTime1 - startTime1) / double(CLOCKS_PER_SEC); // obliczenie czasu trwania

    std::cout << "Compilation time: " << time_taken1 << " s" << std::endl;
    return 0;
}
