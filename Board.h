//
// Created by szymo on 26.04.2023.
//
#include <iostream>
#include "MyVector.h"
#include "MyString.h"
#include "AdjacencyList.h"


#ifndef INC_4_IN_BOARD_H
#define INC_4_IN_BOARD_H

struct Coordinates{
    int x{};
    int y{};
    Coordinates(int x, int y):x{x}, y{y}{}
    Coordinates():x{0}, y{0}{}
};


class Board {
public:
    char *board;
    int size;
    int height;
    int width;
    MyVector <Coordinates> cities;

    Board(int height, int width):height{height}, width{width}, size{height * width}{
        board = new char[size];
    }

    void laodBoard(){
        char c;
        for(int i = 0; i < size; i++){
            c = getchar();
            while (c == '\n') {
                c = getchar();
            }
            board[i] = c;
            if(c == '*'){
                Coordinates coordinates1(i / width, i % width);
                cities.pushBack(coordinates1);
            }
        }
    }

    char getIndex(int i, int j) const{
        int index = i * width + j;
        return board[index];
    }

    ~Board(){
            delete [] board;
    }

    bool isInBoard(int i, int j) const{
        return i >= 0 && i < height && j >= 0 && j < width;
    }

    MyString checkTop(int i, int j) const{
        MyString name = "";


        if(i-1 >= 0 && this->getIndex(i-1,j)!= '.' && this->getIndex(i-1,j) != '#' && this->getIndex(i-1,j)!= ' '){
            if(j> 0 && this->getIndex(i-1,j-1) == '.' || this->getIndex(i-1,j-1) == '#' || this->getIndex(i-1,j-1) == ' '){
                while(j < width &&this->getIndex(i-1,j) != '#' && this->getIndex(i-1,j) != '.' && this->getIndex(i-1,j) != ' '){
                    name += this->getIndex(i-1,j);
                    j++;
                }
            }
            else if(j==0){
                while(j < width &&this->getIndex(i-1,j) != '#' && this->getIndex(i-1,j) != '.' && this->getIndex(i-1,j) != ' '){
                    name += this->getIndex(i-1,j);
                    j++;
                }
            }
            else{
                if(j<width && MyString::isLetter(this->getIndex(i-1,j+1))) return "";
                while(this->getIndex(i-1,j) != '#' && this->getIndex(i-1,j) != '.' && this->getIndex(i-1,j) != ' '){
                    name += this->getIndex(i-1,j);
                    j--;
                }
                name.reverse();
            }
        }
        return name;
    }

    MyString checkBottom(int i, int j) const{
        MyString name = "";
        if(i+1 < height && this->getIndex(i+1,j) != '.' && this->getIndex(i+1,j) != '#' && this->getIndex(i+1,j) != ' '){
            if(j> 0 && (this->getIndex(i+1,j-1) == '.' || this->getIndex(i+1,j-1) == '#' || this->getIndex(i+1,j-1) == ' ')){
                while(j < width && this->getIndex(i+1,j) != '#' && this->getIndex(i+1,j) != '.' && this->getIndex(i+1,j) != ' '){
                    name += this->getIndex(i+1,j);
                    j++;
                }
            }
            else if(j==0){
                while(j < width && this->getIndex(i+1,j) != '#' && this->getIndex(i+1,j) != '.' && this->getIndex(i+1,j) != ' '){
                    name += this->getIndex(i+1,j);
                    j++;
                }
            }
            else if(j==width-1){
                while(j >= 0 && this->getIndex(i+1,j) != '#' && this->getIndex(i+1,j) != '.' && this->getIndex(i+1,j) != ' '){
                    name += this->getIndex(i+1,j);
                    j--;
                }
                name.reverse();
            }
            else{
                if(j<width && MyString::isLetter(this->getIndex(i+1,j+1))) return "";
                while(this->getIndex(i+1,j) != '#' && this->getIndex(i+1,j) != '.' && this->getIndex(i+1,j) != ' '){
                    name += this->getIndex(i+1,j);
                    j--;
                }
                name.reverse();
            }
        }
        return name;
    }

    MyString checkRightBottomCorner(int i, int j) const{
        MyString name = "";
        if((i+1 < height&&j+1 < width) &&this->getIndex(i+1,j+1) != '.' && this->getIndex(i+1,j+1) != '#' && this->getIndex(i+1,j+1) != ' '){
            if(this->getIndex(i+1,j) == '.' || this->getIndex(i+1,j) == '#' || this->getIndex(i+1,j) == ' '){
                while(this->getIndex(i+1,j+1) != '#' && this->getIndex(i+1,j+1) != '.' && this->getIndex(i+1,j+1) != '*' && this->getIndex(i+1,j+1) != ' '){
                    name += this->getIndex(i+1,j+1);
                    j++;
                }
            }
            else{
                if(isInBoard(i+1,j+2) && isInBoard(i+1,j-1)&& MyString::isLetter(this->getIndex(i+1,j+2)) && MyString::isLetter(this->getIndex(i+1,j-1))) return "";
                while(this->getIndex(i+1,j+1) != '#' && this->getIndex(i+1,j+1) != '.' && this->getIndex(i+1,j+1) != '*' && this->getIndex(i+1,j+1) != ' '){
                    name += this->getIndex(i+1,j+1);
                    j--;
                }
                name.reverse();
            }
        }
        return name;
    }

    MyString checkLeftBottom(int i, int j)const{
        MyString name = "";
        if((i+1 < height&&j-1 >= 0) &&this->getIndex(i+1,j-1) != '.' && this->getIndex(i+1,j-1) != '#' && this->getIndex(i+1,j-1) != ' '){
            if(this->getIndex(i+1,j) == '.' || this->getIndex(i+1,j) == '#' || this->getIndex(i+1,j) == ' '){

                while(this->getIndex(i+1,j-1) != '#' && this->getIndex(i+1,j-1) != '.' && this->getIndex(i+1,j-1) != '*' && this->getIndex(i+1,j-1) != ' '){
                    name += this->getIndex(i+1,j-1);
                    j--;
                }
                name.reverse();
            }
            else{
                if(isInBoard(i+1,j+1)&& isInBoard(i+1,j-2) && MyString::isLetter(this->getIndex(i+1,j-2)) && MyString::isLetter(this->getIndex(i+1,j+1))) return "";
                while(this->getIndex(i+1,j-1) != '#' && this->getIndex(i+1,j-1) != '.' && this->getIndex(i+1,j-1) != '*' && this->getIndex(i+1,j-1) != ' '){
                    name += this->getIndex(i+1,j-1);
                    j++;
                }
            }
        }
        return name;
    }

    MyString checkRightTopCorner(int i, int j)const{
        MyString name = "";
        if((i-1 >= 0&&j+1 < width) && this->getIndex(i-1,j+1) != '.' && this->getIndex(i-1,j+1) != '#' && this->getIndex(i-1,j+1) != '*'){
            if(this->getIndex(i-1,j) == '.' || this->getIndex(i-1,j) == '#' || this->getIndex(i-1,j) == '*' || this->getIndex(i-1,j) == ' '){
                while(this->getIndex(i-1,j+1) != '#' && this->getIndex(i-1,j+1) != '.' && this->getIndex(i-1,j+1) != '*' && this->getIndex(i-1,j+1) != ' '){
                    name += this->getIndex(i-1,j+1);
                    j++;
                }
            }
            else{
                if(j<width && MyString::isLetter(this->getIndex(i-1,j+2))) return "";
                while(this->getIndex(i-1,j+1) != '#' && this->getIndex(i-1,j+1) != '.' && this->getIndex(i-1,j+1) != '*' && this->getIndex(i-1,j+1) != ' '){
                    name += this->getIndex(i-1,j+1);
                    j--;
                }
                name.reverse();
            }
        }
        return name;
    }

    MyString checkLeftTopCorner(int i, int j)const{
        MyString name = "";
        if((i-1 >= 0 && j-1 < width) && this->getIndex(i-1,j-1) != '.' && this->getIndex(i-1,j-1) != '#' && this->getIndex(i-1,j-1) != ' '){
            if(this->getIndex(i-1,j) == '.' || this->getIndex(i-1,j) == '#' || this->getIndex(i-1,j) == ' '){
                while(this->getIndex(i-1,j-1) != '#' && this->getIndex(i-1,j-1) != '.' && this->getIndex(i-1,j-1) != '*' && this->getIndex(i-1,j-1) != ' '){
                    name += this->getIndex(i-1,j-1);
                    j--;
                }
                name.reverse();
            }
            else{
                while(this->getIndex(i-1,j-1) != '#' && this->getIndex(i-1,j-1) != '.' && this->getIndex(i-1,j-1) != '*' && j!=width+1 && this->getIndex(i-1,j-1) != ' '){
                    name += this->getIndex(i-1,j-1);
                    j++;
                }
            }
        }
        return name;
    }


    MyString findCityName(int i, int j) const{
        MyString name ="";
        //top
        if(name == "") name = checkTop(i,j);

        //bottom
        if(name == "")name = checkBottom(i,j);

        //right
        if(name == ""){
            if(j+1 < width  && this->getIndex(i,j+1) != '.' && this->getIndex(i,j+1) != '#' && this->getIndex(i,j+1) != ' '){
                while(j+1 < width && this->getIndex(i,j+1) != '#' && this->getIndex(i,j+1) != '.' && this->getIndex(i,j+1) != '*' && this->getIndex(i,j+1) != ' '){
                    name += this->getIndex(i,j+1);
                    j++;
                }
            }
        }

        //left
        if(name == ""){
            if((j-1 >= 0) && this->getIndex(i,j-1) != '.' && this->getIndex(i,j-1) != '#' && this->getIndex(i,j-1) != ' '){
                while(this->getIndex(i,j-1) != '#' && this->getIndex(i,j-1) != '.' && this->getIndex(i,j-1) != '*' && this->getIndex(i,j-1) != ' '){
                    name += this->getIndex(i,j-1);
                    j--;
                }
                name.reverse();
            }
        }
        //right bottom corner
        if(name == "")name = checkRightBottomCorner(i,j);

        //left bottom corner
        if(name == "")name = checkLeftBottom(i,j);

        //right top corner
        if(name == "")name = checkRightTopCorner(i,j);

        //left top corner
        if(name == "")name = checkLeftTopCorner(i,j);
        return name;
    }

};


#endif //INC_4_IN_BOARD_H
