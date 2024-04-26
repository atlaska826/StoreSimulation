#include "LinkedList.h"

LinkedList::LinkedList() {
    headPtr = nullptr;
}

void LinkedList::addElement(listType d) {
    Node *newNode = new Node;
    newNode->data = d;
    newNode->nextPtr = nullptr;

    if (headPtr == nullptr) {
        headPtr = newNode;
    } else if (newNode->data.enterQTime < headPtr->data.enterQTime) {
        newNode->nextPtr = headPtr;
        headPtr = newNode;
    } else {
        Node *tempNode = headPtr;
        while (tempNode->nextPtr != nullptr &&
               tempNode->nextPtr->data.enterQTime < newNode->data.enterQTime) {
            tempNode = tempNode->nextPtr;
        }
        newNode->nextPtr = tempNode->nextPtr;
        tempNode->nextPtr = newNode;
    }
}

void LinkedList::delElement() {
    if (!listIsEmpty()) {
        Node *tempNode = headPtr;
        headPtr = headPtr->nextPtr;
        delete tempNode;
        tempNode = nullptr;
    }
}

listType LinkedList::peek() {
    listType tempData;
    if (!listIsEmpty()) {
        tempData = headPtr->data;
    }
    return tempData;
}

bool LinkedList::listIsEmpty() {
    return headPtr == nullptr;
}

void LinkedList::printList() {
    Node *tempNode = headPtr;
    while (tempNode != nullptr) {
        cout << "CART #" << tempNode->data.cartID
             << " -- Item Count: " << tempNode->data.itemCount
             << " -- Enter Queue Time: " << tempNode->data.enterQTime
             << endl;
        tempNode = tempNode->nextPtr;
    }
}
