#pragma once

#include <iostream>

using namespace std;

struct queueData {
    int totalCustomers = 0; // Total number of customers helped throughout the day
    int queueCount = 0; // Current queue length
    int totalIdleTime = 0; // If queueCount == 0, this is incremented
    int totalOverTime = 0; // Increment if currentTime > 720 & there are people in line
    int maxQueueLength = 0; // If current queueCount > maxQueueLength, reset
    int currItems = 0; // Updated as customers are being removed/added to the queue
    int totalItems = 0; // Running count of items purchased
};

struct queueNodeData {
    int timeAvailable; // Clock time when the current customer is dequeued
    int itemCount; // Number of items of current customer
};

struct queueNode {
    queueNodeData data;
    queueNode *nextPtr;
};

class Queue {
private:
    queueNode *front;
    queueNode *rear;

public:
    Queue();
    queueData lineData;

    void enQueue(queueNodeData d);
    queueNodeData deQueue();
    queueNodeData peek();
    bool queueIsEmpty();
    void printQueue();
};
