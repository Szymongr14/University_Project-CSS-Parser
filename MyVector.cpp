#include "MyVector.h"

MyVector::MyVector() : arr(nullptr), capacity(0), size(0) {}

MyVector::MyVector(int initialCapacity) : arr(new MyString[initialCapacity]), capacity(initialCapacity), size(0) {}

MyVector::MyVector(const MyVector& other) : arr(new MyString[other.capacity]), capacity(other.capacity), size(other.size) {
    for (int i = 0; i < size; i++) {
        arr[i] = other.arr[i];
    }
}


MyVector::MyVector(MyVector&& other) noexcept : arr(other.arr), capacity(other.capacity), size(other.size) {
    other.arr = nullptr;
    other.capacity = 0;
    other.size = 0;
}


void MyVector::pushBack(const MyString& element) {
    if (size >= capacity) {
        resize();
    }
    arr[size++] = element;
}


MyString& MyVector::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    return arr[index];
}


MyVector& MyVector::operator=(const MyVector& other) {
    if (this != &other) {
        delete[] arr;
        arr = new MyString[other.capacity];
        capacity = other.capacity;
        size = other.size;
        for (int i = 0; i < size; i++) {
            arr[i] = other.arr[i];
        }
    }
    return *this;
}

MyVector& MyVector::operator=(MyVector&& other) noexcept {
    if (this != &other) {
        delete[] arr;
        arr = other.arr;
        capacity = other.capacity;
        size = other.size;
        other.arr = nullptr;
        other.capacity = 0;
        other.size = 0;
    }
    return *this;
}

void MyVector::remove(const MyString& value) {
    int index = 0;
    while (index < size) {
        if (arr[index] == value) {
            for (int i = index; i < size - 1; i++) {
                arr[i] = arr[i + 1];
            }
            size--;
        }
        else {
            index++;
        }
    }
}


void MyVector::removeGivenIndex(int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of range");
    }
    for (int j = i; j < size - 1; j++) {
        arr[j] = arr[j + 1];
    }
    size--;
}


bool MyVector::valueExist(MyString value) {
    for (int i = 0; i < this->getSize(); i++) {
        if (this->arr[i] == value) return true;
    }
    return false;
}


int MyVector::indexOfValue(MyString value) {
    for (int i = 0; i < this->getSize(); i++) {
        if (this->arr[i] == value) return i;
    }
    return 1;
}

void MyVector::resize() {
    if (capacity == 0) {
        capacity = 1;
        arr = new MyString[capacity];
    }
    else {
        capacity *= 2;
        MyString* newArr = new MyString[capacity];
        for (int i = 0; i < size; i++) {
            newArr[i] = arr[i];
        }
        delete[] arr;
        arr = newArr;
    }
}

void MyVector::clear() {
    delete[] arr;
    arr = new MyString[capacity];
    size = 0;
}