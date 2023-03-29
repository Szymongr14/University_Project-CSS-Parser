#pragma once
#include <iostream>
#include <stdexcept>
#include "MyString.h"


class MyVector {
private:
    MyString* arr;
    int capacity;
    int size;

public:
    MyVector();
    MyVector(int initialCapacity);
    MyVector(const MyVector& other);
    MyVector(MyVector&& other) noexcept;
    ~MyVector() {delete[] arr;}


    int getSize() const {return size;}
    void pushBack(const MyString& element);
    void remove(const MyString& value);
    void removeGivenIndex(int i);
    bool valueExist(MyString value);
    int indexOfValue(MyString value);
    void clear();


    MyString& operator[](int index);
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other) noexcept;


private:
    void resize();
};


