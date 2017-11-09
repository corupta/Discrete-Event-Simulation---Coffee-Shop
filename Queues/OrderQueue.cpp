//
// Created by corupta on 09.11.2017.
//

#include "OrderQueue.h"

OrderQueue::OrderQueue() : maxLen(0) {}

void OrderQueue::pushCustomer(Customer * customer) {
  orderQueue.push(customer);
}

Customer* OrderQueue::popCustomer() {
  Customer* customer = orderQueue.front();
  orderQueue.pop();
  return customer;
}

bool OrderQueue::empty() {
  return orderQueue.empty();
}

void OrderQueue::updateMaxLen() {
  unsigned int tmp = orderQueue.size();
  maxLen = max(maxLen, tmp);
}

unsigned int OrderQueue::getMaxLen() {
  return maxLen;
}