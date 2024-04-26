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
// PRE: FIXME
// POST: FIXME

void outputReport(vector<Queue> queues);
// PRE: Takes in vector of Queue objects
// POST: Outputs simulation report