//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_CUSTOMER_H
#define PROJECT2_CUSTOMER_H

#include "Person.h"

class Customer : public Person {
  double arrival, order, brew, price, finish;
public:
  Customer(double, double, double, double);

  double getArrival();

  double getOrder();

  double getBrew();

  double getPrice();

  void setFinish(double);

  double getTurnaround();
};


#endif //PROJECT2_CUSTOMER_H
