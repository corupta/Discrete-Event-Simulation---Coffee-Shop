//
// Created by corupta on 09.11.2017.
//

#include "BrewQueue.h"

BrewQueue::BrewQueue() : maxLen(0) {}

bool BrewQueue::CompareCustomer::operator()(Customer * a, Customer * b) {
  // return true if a's price is lower
  return a->getPrice() < b->getPrice();
}

void BrewQueue::pushCustomer(Customer * customer) {
  brewQueue.push(customer);
}

Customer* BrewQueue::popCustomer() {
  Customer* customer = brewQueue.top();
  brewQueue.pop();
  return customer;
}

bool BrewQueue::empty() {
  return brewQueue.empty();
}

void BrewQueue::updateMaxLen() {
  unsigned int tmp = brewQueue.size();
  maxLen = max(maxLen, tmp);
}

unsigned int BrewQueue::getMaxLen() {
  return maxLen;
}