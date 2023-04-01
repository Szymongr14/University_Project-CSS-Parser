#pragma once
#include <iostream>
#include "MyString.h"
#include "MyVector.h"
const int T = 8;


class Block {
public:
    MyVector selectors;
    MyVector attributes;
    MyVector values;
    int globalAttributes = 0;

    void deleteData() {
        selectors.clear();
        attributes.clear();
        values.clear();
        globalAttributes = 0;
    }
};

class Node {
public:
    Block sections[T];
    int isUsed[T];
    Node* next;
    Node* prev;

    Node()
        : next{ nullptr }, prev{ nullptr } {
        for (int i = 0; i < T; i++) {
            isUsed[i] = 0;
        }
    }

    int getIndexOfLastUsed() {
        for (int i = T; i > 0; i--) {
            if (isUsed[i - 1] == 1)return i;
        }
        return -1;
    }

    int returnNumberOfActiveSections() {
        int a = 0;
        for (int i = 0; i < T; i++) {
            if (isUsed[i] == 1)a++;
        }
        return a;
    }
};


class CSSList {
private:
    Node* head;
    Node* tail;
    int totalSections;
public:
    CSSList()
        : head{ nullptr }, tail{ nullptr }, totalSections{ 0 } {}


    void addSectionInBlock(MyVector& selectors, MyVector& attributes, MyVector& values) {
        //first node
        if (head == nullptr) {
            head = new Node();
            tail = head;
        }
        //checking if index of last used is more equal than 0 if not create new node
        else if ((T - 1) - (tail->getIndexOfLastUsed()) <= 0) {
            Node* newNode = new Node();
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }

        int index_of_free_element = tail->getIndexOfLastUsed() + 1;
        Block& currentBlock = tail->sections[index_of_free_element];

        currentBlock.selectors = selectors;
        currentBlock.attributes = attributes;
        currentBlock.values = values;
        tail->isUsed[index_of_free_element] = 1;
        totalSections++;
    }

    void removeSection(int n) {
        //removing specified n-th section
        Node* currentNode = returnWhereIsSection(n);
        Block *section = returnSpecifiedSection(n);
        int index_of_section = returnIndexInBlock(n);
        section->deleteData();
        totalSections--;
        currentNode->isUsed[index_of_section] = 0;

        //checking if current node is empty and remove it
        if (currentNode->returnNumberOfActiveSections() <= 0) {
            removeNode(currentNode);
        }

    }

    void removeNode(Node* nodeToRemove) {
        //first node
        if (nodeToRemove->prev == nullptr) {
            Node* temp = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
            return;
        }

        //last node
        if (nodeToRemove->next == nullptr) {
            Node* temp = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
            delete temp;
            return;
        }

        nodeToRemove->prev->next = nodeToRemove->next;
        nodeToRemove->next->prev = nodeToRemove->prev;
        delete nodeToRemove;
    }



    Node* returnWhereIsSection(int n) {
        int a = 0;
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    a++;
                    if (n == a) {
                        return tempNode;
                    }
                }
            }
            tempNode = tempNode->next;
        }
        return nullptr;
    }

    int returnIndexInBlock(int n) {
        int a = 0;
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    a++;
                    if (n == a) {
                        return j;
                    }
                }
            }
            tempNode = tempNode->next;
        }
        return 0;
    }


    int getNumberOfSections() const{
        return totalSections;
    }

    void printAV() {
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    for (int f = 0; f < tempNode->sections[j].attributes.getSize(); f++) {
                        std::cout << tempNode->sections[j].attributes[f] << " : " << tempNode->sections[j].values[f] << std::endl;
                    }
                }
            }
            tempNode = tempNode->next;
        }
    }

    int countSelectorsInSection(int n) {
        Block *section = returnSpecifiedSection(n);
        return section->selectors.getSize();
    }

    int countAttributesInSection(int n) {
        Block *section = returnSpecifiedSection(n);
        return (section->attributes.getSize() - section->globalAttributes);
    }

    int totalOfAttribute(MyString& value) {
        Node* tempNode = head;
        int i = 0;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    if(tempNode->sections[j].attributes.valueExist(value)) i++;
                }
            }
            tempNode = tempNode->next;
        }
        return i;
    }

    bool AttributeExist(int i, MyString& attribute) {
        Block *section = returnSpecifiedSection(i);
        return section->attributes.valueExist(attribute);
    }


    void removeAttribute(int i, MyString& attribute) {
        Block *section = returnSpecifiedSection(i);
        int f = section->attributes.indexOfValue(attribute);
        MyString value = section->values[f];
        section->attributes.remove(attribute);
        section->values.remove(value);
        if (section->attributes.getSize() < 1) {
            this->removeSection(i);
        }
    }

    Block* returnSpecifiedSection(int n) {
        int a = 0;
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    a++;
                    if (n == a) {
                        return &(tempNode->sections[j]);
                    }
                }
            }
            tempNode = tempNode->next;
        }
        return nullptr;
    }


    MyString returnValueOfAttribute(int i, MyString& attribute) {
        Block *section = returnSpecifiedSection(i);
        int j = section->attributes.indexOfValue(attribute);
        return section->values[j];
    }

    int totalOfSelector(MyString& value) {
        Node* tempNode = head;
        int i = 0;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    if (tempNode->sections[j].selectors.valueExist(value)) i++;
                }
            }
            tempNode = tempNode->next;
        }
        return i;
    }

    MyString returnSelectorInSection(int i, int j) {
        Block *section = returnSpecifiedSection(i);
        return section->selectors[j - 1];
    }

    bool selectorExist(MyString& selector) {
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    if (tempNode->sections[j].selectors.valueExist(selector))return true;
                }
            }
            tempNode = tempNode->next;
        }
        return false;
    }

    MyString lastAttributeOfSelector(MyString& selector, MyString& attribute) {
        Node* tempNode = tail;
        while (tempNode != nullptr) {
            for (int j = T-1; j >=0; j--) {
                if (tempNode->isUsed[j] == 1){
                    if (tempNode->sections[j].selectors.valueExist(selector)) {
                        if (tempNode->sections[j].attributes.valueExist(attribute)) {
                            int index = tempNode->sections[j].attributes.indexOfValue(attribute);
                            return tempNode->sections[j].values[index];
                        }
                    }
                }
            }
            tempNode = tempNode->prev;
        }
        return "0";
    }

    void addAttributeToAll(MyString& attribute, MyString& value) {
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = T - 1; j > 0; j--) {
                if (tempNode->isUsed[j] == 1) {
                    if (!tempNode->sections[j].attributes.valueExist(attribute)) {
                        tempNode->sections[j].globalAttributes++;
                    }
                    if (tempNode->sections[j].attributes.valueExist(attribute)) {
                        int f = tempNode->sections[j].attributes.indexOfValue(attribute);
                        tempNode->sections[j].attributes.removeGivenIndex(f);
                        tempNode->sections[j].values.removeGivenIndex(f);
                    }
                    tempNode->sections[j].attributes.pushBack(attribute);
                    tempNode->sections[j].values.pushBack(value);
                }
            }
            tempNode = tempNode->next;
        }
    }
};


class CssEngine
{
public:
    void addNewSection(MyString &section, CSSList& list) {
        MyVector selectors, attributes, values;

        MyString selector, value, attribute;
        selector = "";

        bool first_value_flag;//helper variable to spot space inside value 
        bool reading_selector = true;
        bool reading_attribute = false;
        bool reading_value = false;

        for (int i = 0; i < section.length(); i++) {
            if (section[i] == '{') {
                reading_selector = false;
                reading_attribute = true;
            }
            else if (section[i] == ':' && !reading_selector) {
                reading_attribute = false;
                reading_value = true;
                first_value_flag = 0;
            }
            else if (section[i] == ';') {
                reading_attribute = true;
                reading_value = false;
                if (attributes.valueExist(attribute)) {
                    int i = attributes.indexOfValue(attribute);
                    attributes.removeGivenIndex(i);
                    values.removeGivenIndex(i);
                }
                attributes.pushBack(attribute);
                values.pushBack(value);
                attribute = "";
                value = "";
            }
            else if (section[i] == ',' && !reading_value) {
                if (selector != "") {
                    selector.trim();
                    selectors.pushBack(selector);
                }
                selector = "";
            }
            else if (section[i] == '}') {
                if (attribute != "") {
                    if (attributes.valueExist(attribute)) {
                        int i = attributes.indexOfValue(attribute);
                        attributes.removeGivenIndex(i);
                        values.removeGivenIndex(i);
                    }
                    attributes.pushBack(attribute);
                    values.pushBack(value);
                }
                if (selector != "") {
                    selector.trim();
                    selectors.pushBack(selector);
                }
                selector = "";
                reading_selector = true;
            }
            else if (reading_selector) {
                selector += section[i];
            }
            else if ((section[i] != '\n' && section[i] != ' ') || (section[i] == ' ' && reading_value && first_value_flag)) {
                if (reading_attribute && section[i] != '\t') {
                    attribute += section[i];
                }
                else if (reading_value && section[i] != '\t') {
                    value += section[i];
                    first_value_flag = 1;
                }
            }

            // last attribute without ';'
            if (i == section.length() - 1 && section[i] == ';') {
                if (reading_attribute) {
                    if (attributes.valueExist(attribute)) {
                        int i = attributes.indexOfValue(attribute);
                        attributes.removeGivenIndex(i);
                        values.removeGivenIndex(i);
                    }
                    attributes.pushBack(attribute);
                }
                if (reading_value) {
                    values.pushBack(value);
                }
            }
        }

        //section without selectors
        if (selectors.getSize() != 0)list.addSectionInBlock(selectors, attributes, values);
        else {
            list.addSectionInBlock(selectors, attributes, values);
            handleSectionWithoutSelectors(list, selectors, attributes, values);
        }
    }


    void handleSectionWithoutSelectors(CSSList& list, MyVector& selectors, MyVector& attributes, MyVector& values) {
        for (int i = 0; i < attributes.getSize(); i++) {
            list.addAttributeToAll(attributes[i], values[i]);
        }
    }

    void ParseCommand(MyString &command, CSSList& list) {
        //pasrsing each element of command to vector
        MyVector tokens;
        MyString tempToken;
        for (int i = 0; i < command.length()+1; i++) {
            if (command[i] == ',' || i==command.length()) {
                tokens.pushBack(tempToken);
                tempToken = "";
                continue;
            }
            tempToken += command[i];
        }
        if (tokens.getSize() > 3) return;
        //i,S,?     z,S,?
        if (tokens.valueExist("S") && tokens.valueExist("?")) {
            if (MyString::isDigit(tokens[0])) {
                PrintNumberOfSelectorsInSection(list, MyString::stringToInt(tokens[0]), command);
            }
            else {
                PrintTotal(command, list.totalOfSelector(tokens[0]));
            }
        }
        //i,A,?    n,A,?
        else if (tokens.valueExist("A") && tokens.valueExist("?")) {
            if (MyString::isDigit(tokens[0])) {
                PrintNumberOfAttributesInSection(list, MyString::stringToInt(tokens[0]), command);
            }
            else {
                PrintTotal(command, list.totalOfAttribute(tokens[0]));
            }
        }
        //i,A,n
        else if (tokens.valueExist("A")) {
            int i = MyString::stringToInt(tokens[0]);
            if (i > list.getNumberOfSections() || i == 0) return;
            if (!list.AttributeExist(i,tokens[2])) return;
            std::cout << command << " == " << list.returnValueOfAttribute(i,tokens[2]) << std::endl;
        }

        //i,S,j
        else if (tokens.valueExist("S")) {
            int i = MyString::stringToInt(tokens[0]);
            int j = MyString::stringToInt(tokens[2]);
            if (i > list.getNumberOfSections() || i == 0) return;
            if (j > list.countSelectorsInSection(i)) return;
            std::cout << command << " == " << list.returnSelectorInSection(i, j) << std::endl;
        }

        //z,E,n
        else if (tokens.valueExist("E")) {
            if (list.selectorExist(tokens[0])) {
                if (list.lastAttributeOfSelector(tokens[0], tokens[2]) != "0") {
                    std::cout << command << " == " << list.lastAttributeOfSelector(tokens[0], tokens[2]) << std::endl;
                }
            }
            return;
        }

        //i,D,*
        else if (tokens.valueExist("D") && tokens.valueExist("*")) {
            int i = MyString::stringToInt(tokens[0]);
            if (i > list.getNumberOfSections() || i == 0) return;
            list.removeSection(i);
            std::cout << command << " == " << "deleted" << std::endl;
        }

        //i,D,n
        else if (tokens.valueExist("D")) {
            int i = MyString::stringToInt(tokens[0]);
            if (i > list.getNumberOfSections() || i == 0) return;
            if (!list.AttributeExist(i, tokens[2])) return;
            list.removeAttribute(i,tokens[2]);
            std::cout << command << " == " << "deleted" << std::endl;
        }
    }

    void PrintNumberOfSelectorsInSection(CSSList& list, int i, MyString &command) {
        if (i > list.getNumberOfSections() || i==0) return;
        std::cout << command << " == " << list.countSelectorsInSection(i) << std::endl;
    }

    void PrintTotal(MyString &command,int value) {
        std::cout << command << " == " << value << std::endl;
    }

    void PrintNumberOfAttributesInSection(CSSList& list, int i, MyString &command) {
        if (i > list.getNumberOfSections() || i == 0) return;
        std::cout << command << " == " << list.countAttributesInSection(i) << std::endl;
    }



    void init() {
        CSSList list;
        char current_char;
        MyString current_line = "";
        MyString section = "";
        MyString code = "";
        bool analyzing_code = true;
        bool inSection = 0;
        bool sectionBreak = false;

        while (std::cin.get(current_char)) {
            if (current_char == '\n') {
                if (current_line.exist(';') && !inSection) {
                    //std::cout << "globalny" << std::endl;
                    current_line = "";
                    continue;
                }
                if (current_line == "\n") continue;
                if (current_line == (MyString)"????") {
                    analyzing_code = false;
                    current_line = "";
                    continue;
                }

                if (current_line == (MyString)"****") {
                    analyzing_code = true;
                    current_line = "";
                    continue;
                }

                if (analyzing_code) {
                    for (int i = 0; i < current_line.length(); i++) {
                        if (current_line[i] != '}') {
                            section += current_line[i];
                        }
                        else {
                            section+='}';
                            addNewSection(section, list);
                            //list.PrintAttributesAndValues();
                            //list.printAV();
                            inSection = 0;
                            section = "";
                        }
                    }
                }
                else {
                    if (current_line == "?") {
                        std::cout << "? == " << list.getNumberOfSections() << std::endl;
                        current_line = "";
                        continue;
                    }
                    ParseCommand(current_line, list);
                }
                current_line = "";
            }
            else {
                if (current_char == '{') inSection = 1;
                current_line+=current_char;
            }
        }
        //checking if last command has '\n'
        if (current_line.length() > 0) {
            if (current_line == "?") {
                std::cout << "? == " << list.getNumberOfSections() << std::endl;
                current_line = "";
            }
            else {
                ParseCommand(current_line, list);

            }
        }
    }
};

