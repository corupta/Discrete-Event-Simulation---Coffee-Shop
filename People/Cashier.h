//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_CASHIER_H
#define PROJECT2_CASHIER_H

#include "Employee.h"

class Cashier : public Employee {
public:
  Cashier();
  void newCustomer(Customer* customer) override; // override virtual function
};


#endif //PROJECT2_CASHIER_H
