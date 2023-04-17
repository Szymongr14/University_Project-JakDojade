#include <iostream>
#include "MyVector.hxx"
#include "MyString.h"
#include "AdjacencyList.h"


MyString findCityName(const char** arr, int height, int width, int i, int j){
    MyString name ="";

    //bottom
    if(i+1 < height && arr[i+1][j] != '.' && arr[i+1][j] != '#'){
        if(j> 0 && (arr[i+1][j-1] == '.' || arr[i+1][j-1] == '#')){
            while(j < width && arr[i+1][j] != '#' && arr[i+1][j] != '.'){
                name += arr[i+1][j];
                j++;
            }
        }
        else if(j==0){
            while(j < width && arr[i+1][j] != '#' && arr[i+1][j] != '.'){
                name += arr[i+1][j];
                j++;
            }
        }
        else{
            while(arr[i+1][j] != '#' && arr[i+1][j] != '.'){
                name += arr[i+1][j];
                j--;
            }
            name.reverse();
        }
    }

    //top
    else if(i-1 >= 0 && arr[i-1][j] != '.' && arr[i-1][j] != '#'){
        if(j> 0 && arr[i-1][j-1] == '.' || arr[i-1][j-1] == '#'){
            while(j < width &&arr[i-1][j] != '#' && arr[i-1][j] != '.'){
                name += arr[i-1][j];
                j++;
            }
        }
        else if(j==0){
            while(j < width &&arr[i-1][j] != '#' && arr[i-1][j] != '.'){
                name += arr[i-1][j];
                j++;
            }
        }
        else{
            while(arr[i-1][j] != '#' && arr[i-1][j] != '.'){
                name += arr[i-1][j];
                j--;
            }
            name.reverse();
        }
    }

    //right
    else if(j+1 < width  && arr[i][j+1] != '.' && arr[i][j+1] != '#'){
        while(j+1 < width && arr[i][j+1] != '#' && arr[i][j+1] != '.' && arr[i][j+1] != '*'){
            name += arr[i][j+1];
            j++;
        }
    }

    //left
    else if((j-1 >= 0|| j==0) && arr[i][j-1] != '.' && arr[i][j-1] != '#'){
        while(arr[i][j-1] != '#' && arr[i][j-1] != '.' && arr[i][j-1] != '*'){
            name += arr[i][j-1];
            j--;
        }
        name.reverse();
    }

    //TODO: sprawdzic czy nie ma bledu w warunkach, wychodzenie poza tablice
    //right bottom corner
    else if(arr[i+1][j+1] != '.' && arr[i+1][j+1] != '#'){
        while(arr[i+1][j+1] != '#' && arr[i+1][j+1] != '.' && arr[i+1][j+1] != '*'){
            name += arr[i+1][j+1];
            j++;
        }
    }

    //left bottom corner
    else if(arr[i+1][j-1] != '.' && arr[i+1][j-1] != '#'){
        while(arr[i+1][j-1] != '#' && arr[i+1][j-1] != '.' && arr[i+1][j-1] != '*'){
            name += arr[i+1][j-1];
            j--;
        }
        name.reverse();
    }

    //right top corner
    else if(arr[i-1][j+1] != '.' && arr[i-1][j+1] != '#'){
        while(arr[i-1][j+1] != '#' && arr[i-1][j+1] != '.' && arr[i-1][j+1] != '*'){
            name += arr[i-1][j+1];
            j++;
        }
    }

    //left top corner
    else if(arr[i-1][j-1] != '.' && arr[i-1][j-1] != '#'){
        while(arr[i-1][j-1] != '#' && arr[i-1][j-1] != '.' && arr[i-1][j-1] != '*'){
            name += arr[i-1][j-1];
            j--;
        }
        name.reverse();
    }
    return name;
}

void parseArray(const char** arr, int height, int width) {
    AdjacencyList adjList;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (arr[i][j] != '.' && !MyString::isLetter(arr[i][j])) {
                if(arr[i][j] == '*'){
                    std::cout<<findCityName(arr, height, width, i, j)<<std::endl;
                }
            }
        }
    }
}


int main() {
    int height, width;
    char c;
    std::cin >> height >> width;

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


    std::cout << "Array elements: " << std::endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << std::endl;
    }


    parseArray((const char**)board, height, width);



    Edge test{"Olsztyn", 1};
    Edge test11{"Warszawa", 1};
    Edge test12{"Krakow", 1};


    LinkedList list;
    list.addNode(test);
    list.addNode(test11);
    list.addNode(test12);

    Vertex vertex2{"GDansk",list};

    vertex2.printEdges();
    vertex2.edges.addNode(Edge{"Poznan", 50});
    vertex2.printEdges();

    AdjacencyList adjacencyList;
    adjacencyList.addVertex(vertex2);
    adjacencyList.addEdge("GDansk", "ostroda", 30);
    adjacencyList.printList();


    // zwolnienie zaalokowanej pamięci
    for (int i = 0; i < height; i++) {
        delete[] board[i];
    }
    delete[] board;
    return 0;
}
