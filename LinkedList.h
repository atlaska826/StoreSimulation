#pragma once

#include <iostream>

using namespace std;

struct listType {
    int cartID; // Unique ID assigned for each cart
    int itemCount; // Amount of items the customer will get
    int enterQTime; // Current time + shopping time
};

struct Node {
    listType data;
    Node *nextPtr;
};

class LinkedList {
private:
    Node *headPtr;

public:
    LinkedList();

    void addElement(listType d);
    void delElement();
    listType peek();
    bool listIsEmpty();
    void printList();

    static int listCount; // Number of carts currently in the list
};
