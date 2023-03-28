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

    Block returnSpecifiedSection(int n) {
        int a = 0;
        Node* tempNode = head;
        while (tempNode != nullptr) {
            for (int j = 0; j < T; j++) {
                if (tempNode->isUsed[j] == 1) {
                    a++;
                    if (n == a) {
                        return tempNode->sections[j];
                    }
                }
            }
            tempNode = tempNode->next;
        }
        return Block();
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
                        //std::cout << tempNode->sections[j].selectors[f] << std::endl;
                    }
                }
            }
            tempNode = tempNode->next;
        }
    }

    int countSelectorsInSection(int n) {
        Block section = returnSpecifiedSection(n);
        return section.selectors.getSize();
    }

    int countAttributesInSection(int n) {
        Block section = returnSpecifiedSection(n);
        return section.attributes.getSize();
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
        Block section = returnSpecifiedSection(i);
        return section.attributes.valueExist(attribute);
    }

    MyString returnValueOfAttribute(int i, MyString& attribute) {
        Block section = returnSpecifiedSection(i);
        int j = section.attributes.indexOfValue(attribute);
        return section.values[j];
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
        Block section = returnSpecifiedSection(i);
        return section.selectors[j - 1];
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
            for (int j = T-1; j >0; j--) {
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
   /*             if (reading_selector&&section[i] != '\t') {
                    selector += section[i];
                }*/
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
        list.addSectionInBlock(selectors, attributes, values);


        ////section without selectors
        //if (selectors.getSize() != 0)list.addNode(selectors, attributes, values);
        //else {
        //    list.addNode(selectors, attributes, values);
        //    handleSectionWithoutSelectors(list, selectors, attributes, values);
        //}
    }


    //void handleSectionWithoutSelectors(CSSList& list, MyVector& selectors, MyVector& attributes, MyVector& values) {
    //    for (int i = 0; i < attributes.getSize(); i++) {
    //        list.addAttributeToAll(attributes[i], values[i]);
    //    }
    //}

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

        ////i,D,*
        //else if (tokens.valueExist("D") && tokens.valueExist("*")) {
        //    int i = MyString::stringToInt(tokens[0]);
        //    if (i > list.returnNumberOfSection()) return;
        //    list.RemoveNode(i);
        //    std::cout << command << " == " << "deleted" << std::endl;
        //}

        ////i,D,n
        //else if (tokens.valueExist("D")) {
        //    int i = MyString::stringToInt(tokens[0]);
        //    if (i > list.returnNumberOfSection()) return;
        //    if (!list.AttributeExist(i, tokens[2])) return;
        //    list.removeAttribute(i,tokens[2]);
        //    std::cout << command << " == " << "deleted" << std::endl;
        //}
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
                    std::cout << "globalny" << std::endl;
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
                            list.printAV();
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
    }
};

