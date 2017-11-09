//
// Created by corupta on 08.11.2017.
//

#include <stdio.h>
#include "Employee.h"

Employee::Employee(PersonType personType) : Person(personType), busyTime(0), currentCustomer(nullptr) {}

void Employee::setEmployeeId(unsigned int newEmployeeId) {
  employeeId = newEmployeeId;
}

unsigned int Employee::getEmployeeId() {
  return employeeId;
}

Customer *Employee::getCurrentCustomer() {
  return currentCustomer;
}

double Employee::getBusyTime() {
  return busyTime;
}