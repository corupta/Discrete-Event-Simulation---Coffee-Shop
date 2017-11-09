//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_BARISTA_H
#define PROJECT2_BARISTA_H

#include "Employee.h"

class Barista : public Employee {
public:
  Barista();
  void newCustomer(Customer* customer) override; // override virtual function
};


#endif //PROJECT2_BARISTA_H
