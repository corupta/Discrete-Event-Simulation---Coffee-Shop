//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_ORDERQUEUE_H
#define PROJECT2_ORDERQUEUE_H

#include "../People/Customer.h"
#include <queue>

using namespace std;

class OrderQueue {
  // a queue of customers, in first in first out mode.
  queue<Customer *> orderQueue;

  // maximum length, this queue have ever been. initially 0
  unsigned int maxLen;

public:

  // constructor that sets the maxlen to 0
  OrderQueue();

  // pushes a customer to the queue
  void pushCustomer(Customer *);

  // pops and returns the customer at the front of the queue
  Customer *popCustomer();

  // return true if the queue is empty.
  bool empty();

  // updates the maximum length, by the current length of the queue
  // only called when all simultaneous events are completed.
  void updateMaxLen();

  // return the maximum length of the queue.
  unsigned int getMaxLen();
};


#endif //PROJECT2_ORDERQUEUE_H
