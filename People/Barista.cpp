//
// Created by corupta on 08.11.2017.
//

#include "Barista.h"

Barista::Barista() : Employee(barista) {}

void Barista::newCustomer(Customer *person) {
  busyTime += person -> getBrew();
  currentCustomer = person;
};