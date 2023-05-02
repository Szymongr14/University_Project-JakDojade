#include <iostream>
#include "MyVector.h"
#pragma once
class MyString
{
private:
	char *str;

public:
    friend std::ostream& operator<<(std::ostream& os, const MyString& object);
    friend std::istream& operator>>(std::istream& is, MyString& object);

    MyString();
    MyString(const MyString& object);
    MyString(MyString&& object) noexcept;
    MyString(const char* text);
    ~MyString();

    int length() const;
    bool stringCompare(const char* text)const;
    bool stringCompare(const MyString string) const;
    bool empty() const {return (str == nullptr);}
    void trim();
    void reverse();


    static bool isLetter(char c) {return isalpha(c) != 0;}
    char static* stringCopy(char* where, const char* from);
    char static* myGetLine();
    bool static isDigit(const MyString value_to_check);
    int static stringToInt(const MyString value);
    bool exist(char c) const;
    static MyString fromCharVector(const MyVector <char>& charVec) {
        MyString result;
        int size = charVec.getSize();
        result.str = new char[size + 1];
        for (std::size_t i = 0; i < size; ++i) {
            result.str[i] = charVec[i];
        }
        result.str[size] = '\0';
        return result;
    }


    MyString& operator=(const MyString& object);
    MyString& operator=(MyString&& other) noexcept;
    bool operator==(const char* text) const {return stringCompare(text);}
    bool operator!=(const char* text) const {return !(stringCompare(text));}
    bool operator==(const MyString value) const{return stringCompare(value);}
    char operator[](int index) const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(char c);






};

