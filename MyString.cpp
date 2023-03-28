#include "MyString.h"

std::ostream& operator<<(std::ostream& os, const MyString& object)
{
	for (int i = 0; i < object.length(); i++) {
		os << object.str[i];
	}
	return os;
}


MyString::MyString() 
    : str(nullptr) {}


MyString::MyString(const MyString& object) {
    int len = 0;
    while (object.str[len] != '\0') {
        ++len;
    }
    str = new char[len + 1];
    for (int i = 0; i <= len; ++i) {
        str[i] = object.str[i];
    }
}


MyString::MyString(MyString&& object) noexcept {
    str = object.str;
    object.str = nullptr;
}


int MyString::length() const {
    int len = 0;
    while (this->str[len] != '\0') {
        ++len;
    }
    return len;
}


MyString::MyString(const char* text) {
    int len = 0;
    while (text[len] != '\0') {
        ++len;
    }
    str = new char[len + 1];
    for (int i = 0; i <= len; ++i) {
        str[i] = text[i];
    }
}


MyString::~MyString() {
    delete[] str;
}


MyString& MyString::operator=(const MyString& object){
    if (this != &object) {
        int len = 0;
        while (object.str[len] != '\0') {
            ++len;
        }
        delete[] str;
        str = new char[len + 1];
        for (int i = 0; i <= len; ++i) {
            str[i] = object.str[i];
        }
    }
    return *this;
}


MyString& MyString::operator=(MyString&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    delete[] str;
    str = other.str;
    other.str = nullptr;
    return *this;
}


char* MyString::stringCopy(char* where, const char* from){
    char* dest_copy = where;
    while (*from != '\0') {
        *dest_copy = *from;
        ++dest_copy;
        ++from;
    }
    *dest_copy = '\0';
    return where;
}


bool MyString::stringCompare(const char* text) const{
    for (int i = 0; i < this->length(); i++) {
        if (this->str[i] != text[i]) return false;
    }
    return true;
}


char MyString::operator[](int index)
{
    return str[index];
}


bool MyString::stringCompare(const MyString string) const {
    const char* str1 = this->str;
    const char* str2 = string.str;
    while (*str1 && (*str1 == *str2)) {
        ++str1;
        ++str2;
    }
    return (*str1 - *str2) == 0;
}


char *MyString::myGetLine()
{
    char* buffer = nullptr;
    int bufferSize = 0;
    int bufferCapacity = 0;
    int c;

    do {
        c = getchar();
        if (c == EOF || c == '\n') {
            break;
        }
        if (bufferSize >= bufferCapacity) {
            bufferCapacity += 128;
            char* newBuffer = new char[bufferCapacity];
            if (buffer != nullptr) {
                MyString::stringCopy(newBuffer, buffer);
                delete[] buffer;
            }
            buffer = newBuffer;
        }
        buffer[bufferSize++] = c;
    } while (true);

    if (buffer == nullptr) {
        buffer = new char[1];
        buffer[0] = '\0';
    }
    else {
        if (bufferSize >= bufferCapacity) {
            bufferCapacity += 1;
            char* newBuffer = new char[bufferCapacity];
            MyString::stringCopy(newBuffer, buffer);
            delete[] buffer;
            buffer = newBuffer;
        }
        buffer[bufferSize] = '\0';
    }

    return buffer;
}


MyString& MyString::operator+=(char c) {
    if (this->str == nullptr) {
        char* newString = new char[2];
        newString[0] = c;
        newString[1] = '\0';
        this->str = newString;
        return *this;
    }
    char* newString = new char[this->length() + 2];
    stringCopy(newString, this->str);
    newString[this->length()] = c;
    newString[this->length() + 1] = '\0';
    delete[] this->str;
    this->str = newString;
    return *this;
}


void MyString::trim() {
    if (str == nullptr) {
        return;
    }
    int start = 0;
    while (str[start] != '\0' && isspace(str[start])) {
        start++;
    }
    int end = length() - 1;
    while (end >= start && isspace(str[end])) {
        end--;
    }
    if (start == 0 && end == length() - 1) {
        return;
    }
    for (int i = start; i <= end; i++) {
        str[i - start] = str[i];
    }
    str[end - start + 1] = '\0';
}


bool MyString::isDigit(const MyString value_to_check) {
    for (int i = 0; i < value_to_check.length(); i++) {
        if (value_to_check.str[i] < '0' || value_to_check.str[i] > '9')
        {
            return false;
        }
    }
    return true;
}

int MyString::stringToInt(const MyString value) {
    int result = 0;
    int sign = 1;
    int i = 0;
    if (value.str[0] == '-') {
        sign = -1;
        i++;
    }
    for (; value.str[i] != '\0'; ++i) {
        result = result * 10 + (value.str[i] - '0');
    }
    return sign * result;
}


std::istream& operator>>(std::istream& is, MyString& object) {
    char* buffer = object.myGetLine();
    object = buffer;
    delete[] buffer;
    return is;
}


MyString& MyString::operator+=(const MyString& other) {
    if (other.str == nullptr) {
        return *this;
    }
    if (this->str == nullptr) {
        char* newString = new char[other.length() + 1];
        stringCopy(newString, other.str);
        this->str = newString;
        return *this;
    }
    char* newString = new char[this->length() + other.length() + 1];
    stringCopy(newString, this->str);
    stringCopy(newString + this->length(), other.str);
    newString[this->length() + other.length()] = '\0';
    delete[] this->str;
    this->str = newString;
    return *this;
}


bool MyString::exist(char c) const {
    for (int i = 0; i < this->length(); i++) {
        if (this->str[i] == c) return true;
    }
    return false;
}





