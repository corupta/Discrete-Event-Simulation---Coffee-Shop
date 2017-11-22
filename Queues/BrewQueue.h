//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_BREWQUEUE_H
#define PROJECT2_BREWQUEUE_H

#include "../People/Customer.h"
#include <queue>

using namespace std;

class BrewQueue {
  // comparator that is used to order the customers by their orders' price in the priority queue
  class CompareCustomer {
  public:
    bool operator()(Customer *, Customer *);
  };

  // a prioirity queue of customers, ordered from highest to lowest order prices of the customers.
  priority_queue<Customer *, vector<Customer *>, CompareCustomer> brewQueue;

  // maximum length, this queue have ever been. initially 0
  unsigned int maxLen;

public:

  // constructor that sets the maxlen to 0
  BrewQueue();

  // pushes a customer to the priority queue
  void pushCustomer(Customer *);

  // pops and returns the customer at the top of the priority queue
  Customer *popCustomer();

  // return true if the priority queue is empty.
  bool empty();

  // updates the maximum length, by the current length of the priority queue
  // only called when all simultaneous events are completed.
  void updateMaxLen();

  // return the maximum length of the queue.
  unsigned int getMaxLen();
};


#endif //PROJECT2_BREWQUEUE_H
