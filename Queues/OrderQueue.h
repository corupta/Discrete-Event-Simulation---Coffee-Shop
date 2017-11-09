//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_ORDERQUEUE_H
#define PROJECT2_ORDERQUEUE_H

#include "../People/Customer.h"
#include <queue>

using namespace std;

class OrderQueue {
  queue<Customer *> orderQueue;
  unsigned int maxLen;
public:
  OrderQueue();

  void pushCustomer(Customer *);

  Customer *popCustomer();

  bool empty();

  void updateMaxLen();

  unsigned int getMaxLen();
};


#endif //PROJECT2_ORDERQUEUE_H
