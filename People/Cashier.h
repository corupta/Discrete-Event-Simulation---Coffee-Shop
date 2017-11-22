//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_CASHIER_H
#define PROJECT2_CASHIER_H

#include "Employee.h"

// inherits from the employee class
class Cashier : public Employee {
public:
  // constructor cosntructs the employee parent with the cashier person type
  Cashier();

  // assigns the customer as the current customer of the current employee
  // increases the busytime by the order time of the customer.
  void newCustomer(Customer* customer) override; // override virtual function
};


#endif //PROJECT2_CASHIER_H
