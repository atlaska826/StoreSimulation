#include "simulation.h"

void customerArrival(int time, int &idNum, LinkedList &shopperList) {
// PRE: Takes in current time, id number, and the shopper list
// POST: Generates random customers, creates their data, and adds them to shopper list
    // Generates random number of customers to arrive at the store
    int numCustomers = rand() % (3 - 1) + 2;

    int itemPercent;
    listType tempShopper;

    // Updates customer data and adds them to Linked List
    for (int i = 0; i < numCustomers; i++) {
        // Assigns the cartID and then increments the value of the variable
        tempShopper.cartID = idNum;
        idNum++;

        // Randomly determines how many items each customer will get
        itemPercent = rand() % (100 - 1) + 1;
        if (itemPercent <= 40) {
            tempShopper.itemCount = rand() % (10 - 1) + 1;
        } else if (itemPercent <= 70) {
            tempShopper.itemCount = rand() % (20 - 11) + 11;
        } else if (itemPercent <= 90) {
            tempShopper.itemCount = rand() % (30 - 21) + 21;
        } else {
            tempShopper.itemCount = rand() % (60 - 31) + 31;
        }

        // Determines shop time and enterQTime for each customer
        int shopTimeSeconds = 0;
        for (int j = 0; j < tempShopper.itemCount; j++) {
            shopTimeSeconds += (rand() % (60 - 30) + 30);
        }
        // Rounds up (>= 30) or down (< 30) to the nearest minute
        int shopMinutes = (shopTimeSeconds + 29) / 60;
        tempShopper.enterQTime = time + shopMinutes;

        // Adds customers to shopperList and increments list count
        shopperList.addElement(tempShopper);
        LinkedList::listCount++;
    }
}

void updateLines(int time, LinkedList &shopperList, vector<Queue> &queues) {
// PRE: Takes in current time, the shopper list, and the vector of Queue objects
// POST: Checks the shopper list and each queue to see if any customers need to be moved in or out of them and updates
//       the object's data accordingly

    // Checks to see if anyone is ready to leave the checkouts
    for (Queue &queue: queues) {
        queueNodeData tempData = queue.peek();
        while (!queue.queueIsEmpty() && tempData.timeAvailable <= time) {
            queue.lineData.queueCount--;
            queue.lineData.currItems -= tempData.itemCount;
            queue.deQueue();

            if (!queue.queueIsEmpty()) {
                tempData = queue.peek();
            } else {
                break;
            }
        }
    }

    // Checks to see if anyone in the store is ready to be added to the checkout line
    listType tempData = shopperList.peek();
    while (tempData.enterQTime == time) {
        // Finds the shortest queue
        int shortest_queue = 0;
        for (int i = 0; i < queues.size(); i++) {
            if (queues[i].lineData.currItems < queues[shortest_queue].lineData.currItems) {
                shortest_queue = i;
            }
        }
        Queue updateQueue = queues[shortest_queue];

        // Updates data for new checkout customer
        queueNodeData tempQueueShopper;
        tempQueueShopper.itemCount = tempData.itemCount;

        // Determines timeAvailable each customer -- checkout time is .15 min (9 seconds) per item
        int checkoutTimeSeconds = tempQueueShopper.itemCount * 9;

        // Rounds up (>= 30) or down (< 30) to the nearest minute
        int checkoutMinutes = (checkoutTimeSeconds + 29) / 60;
        tempQueueShopper.timeAvailable = time + checkoutMinutes;

        // Update currentItems and totalItems for the queue
        updateQueue.lineData.currItems += tempQueueShopper.itemCount;
        updateQueue.lineData.totalItems += tempQueueShopper.itemCount;

        // Updates queue counts and max queue length if necessary
        updateQueue.lineData.queueCount++;
        updateQueue.lineData.totalCustomers++;
        if (updateQueue.lineData.queueCount > updateQueue.lineData.maxQueueLength) {
            updateQueue.lineData.maxQueueLength = updateQueue.lineData.queueCount;
        }

        // Adds checkout customer to update queue
        updateQueue.enQueue(tempQueueShopper);
        queues[shortest_queue] = updateQueue;

        // Deletes shopper from shopperList and decrements list count
        shopperList.delElement();
        LinkedList::listCount--;

        tempData = shopperList.peek();
    }

    // Update all queue statistics
    for (Queue &queue: queues) {
        queueData data = queue.lineData;

        // Updates totalIdleTime
        if (data.queueCount == 0) {
            data.totalIdleTime++;
        }

        // Updates totalOverTime
        if (time > 720 && data.queueCount > 0) {
            data.totalOverTime++;
        }

        queue.lineData = data;
    }
}

void outputReport(vector<Queue> queues) {
// PRE: Takes in vector of Queue objects
// POST: Outputs simulation report
    int width = 25;
    for (int i = 0; i < queues.size(); i++) {
        queueData data = queues[i].lineData;
        cout << "CHECKOUT LINE:\t" << i
             << "\n  " << left << setw(width) << "Total Customers Helped:" << data.totalCustomers
             << "\n  " << setw(width) << "Total Number of Items:" << data.totalItems
             << "\n  " << setw(width) << "Max Line Length:" << data.maxQueueLength
             << "\n  " << setw(width) << "Total Idle Time:" << data.totalIdleTime
             << "\n  " << setw(width) << "Total Over Time:" << data.totalOverTime
             << endl;
    }
}