//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EMPLOYEE_H
#define PROJECT2_EMPLOYEE_H

#include "Customer.h"

class Employee : Person {
  Customer *currentCustomer;
public:
  Employee(PersonType);

  Customer *getCurrentCustomer();

  void newCustomer(Customer *);
};


#endif //PROJECT2_EMPLOYEE_H
