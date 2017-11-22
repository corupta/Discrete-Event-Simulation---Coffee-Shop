//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_BARISTA_H
#define PROJECT2_BARISTA_H

#include "Employee.h"

// inherits from the employee class
class Barista : public Employee {
public:
  // constructor cosntructs the employee parent with the barista person type
  Barista();

  // assigns the customer as the current customer of the current employee
  // increases the busytime by the brew time of the customer.
  void newCustomer(Customer* customer) override; // override virtual function
};


#endif //PROJECT2_BARISTA_H
