//
// Created by corupta on 08.11.2017.
//

#include "Cashier.h"

Cashier::Cashier() : Employee(cashier) {}

void Cashier::newCustomer(Customer *person) {
  busyTime += person -> getOrder();
  currentCustomer = person;
};