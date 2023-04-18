#include <iostream>
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


    char static* stringCopy(char* where, const char* from);
    char static* myGetLine();
    bool static isDigit(const MyString value_to_check);
    int static stringToInt(const MyString value);
    bool exist(char c) const;


    MyString& operator=(const MyString& object);
    MyString& operator=(MyString&& other) noexcept;
    bool operator==(const char* text) const {return stringCompare(text);}
    bool operator!=(const char* text) const {return !(stringCompare(text));}
    bool operator==(const MyString value) const{return stringCompare(value);}
    char operator[](int index) const;
    MyString& operator+=(const MyString& other);
    MyString& operator+=(char c);

    void reverse() {
        int len = this->length();
        for (int i = 0; i < len / 2; i++) {
            char temp = str[i];
            str[i] = str[len - i - 1];
            str[len - i - 1] = temp;
        }
    }

    static bool isLetter(char c) {
        return isalpha(c) != 0;
    }

};

