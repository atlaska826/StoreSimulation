#pragma once

#include <iostream>
#include <random>
#include <iomanip>

#include "LinkedList.h"
#include "Queue.h"

using namespace std;

void customerArrival(int time, int &idNum, LinkedList &shopperList);
// PRE: Takes in current time, id number, and the shopper list
// POST: Generates random customers, creates their data, and adds them to shopper list

void updateLines(int time, LinkedList &shopperList, vector<Queue> &queues);
// PRE: Takes in current time, the shopper list, and the vector of Queue objects
// POST: Checks the shopper list and each queue to see if any customers need to be moved in or out of them and updates
//       the object's data accordingly

void outputReport(vector<Queue> queues);
// PRE: Takes in vector of Queue objects
// POST: Outputs simulation report