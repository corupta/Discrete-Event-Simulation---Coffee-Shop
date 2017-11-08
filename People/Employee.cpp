//
// Created by corupta on 08.11.2017.
//

#include <stdio.h>
#include "Employee.h"

Employee::Employee(PersonType personType) : Person(personType) {
  currentCustomer = NULL;
}

Customer *Employee::getCurrentCustomer() {
  return currentCustomer;
}

void Employee::newCustomer(Customer *person) {
  currentCustomer = person;
};
