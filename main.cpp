#include <iostream>
#include <vector>

#include "LinkedList.h"
#include "Queue.h"
#include "simulation.h"

using namespace std;

int LinkedList::listCount = 0;

bool allQueuesEmpty(const vector<Queue> &queues);

int main() {
    srand(time(0));
    LinkedList shopperList;
    vector<Queue> queues;
    int numLines, idNum = 1;

    // Gets the number of checkout lines from the user
    while (true) {
        cout << "How many checkout lines would you like to simulate (1-10)? ==> ";
        cin >> numLines;

        if (!cin.good()) {
            cout << "INVALID INPUT: You must enter a number.\n";
        } else if (numLines > 10 || numLines < 1) {
            cout << "INVALID INPUT: Number of lines must be between 1 and 10 inclusive.\n";
        } else {
            break;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Create checkout lines
    for (int i = 0; i < numLines; i++) {
        Queue tempQueue;
        queues.push_back(tempQueue);
    }

    // Run simulation
    int time;
    for (time = 0; time <= 720; time++) {
        customerArrival(time, idNum, shopperList);
        updateLines(time, shopperList, queues);
    }

    // Clears out store and finishing checking customers out
    while (!shopperList.listIsEmpty() || !allQueuesEmpty(queues)) {
        updateLines(time, shopperList, queues);
        time++;
    }

    // Prints output report
    outputReport(queues);

    return 0;
}

bool allQueuesEmpty(const vector<Queue> &queues) {
    for (Queue queue: queues) {
        if (!queue.queueIsEmpty()) {
            return false;
        }
    }
    return true;
}
