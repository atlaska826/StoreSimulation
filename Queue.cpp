#include "Queue.h"

Queue::Queue() {
    front = nullptr;
    rear = nullptr;
}

void Queue::enQueue(queueNodeData d) {
    queueNode* newNode = new queueNode;
    newNode->data = d;
    newNode->nextPtr = nullptr;

    if (queueIsEmpty()) {
        front = newNode;
        rear = newNode;
    } else {
        rear->nextPtr = newNode;
        rear = newNode;
    }
}

queueNodeData Queue::deQueue() {
    queueNodeData tempData;
    if (!queueIsEmpty()) {
        queueNode* tempNode = front;
        front = front->nextPtr;

        if (queueIsEmpty()) {
            rear = nullptr;
        }
        delete tempNode;
        tempNode = nullptr;
    }
    return tempData;
}

queueNodeData Queue::peek() {
    queueNodeData tempData;
    if (!queueIsEmpty()) {
        tempData = front->data;
    }
    return tempData;
}

bool Queue::queueIsEmpty() {
    return front == nullptr;
}

void Queue::printQueue() {
    queueNode* tempNode = front;
    while (tempNode != nullptr) {
        cout << tempNode->data.itemCount << " " << tempNode->data.timeAvailable << endl;
        tempNode = tempNode->nextPtr;
    }
}