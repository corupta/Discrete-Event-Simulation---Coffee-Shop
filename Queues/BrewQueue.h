//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_BREWQUEUE_H
#define PROJECT2_BREWQUEUE_H

#include "../People/Customer.h"
#include <queue>

using namespace std;

class BrewQueue {
  class CompareCustomer {
  public:
    bool operator()(Customer *, Customer *);
  };

  priority_queue<Customer *, vector<Customer *>, CompareCustomer> brewQueue;
  unsigned int maxLen;
public:
  BrewQueue();

  void pushCustomer(Customer *);

  Customer *popCustomer();

  bool empty();

  void updateMaxLen();

  unsigned int getMaxLen();
};


#endif //PROJECT2_BREWQUEUE_H
