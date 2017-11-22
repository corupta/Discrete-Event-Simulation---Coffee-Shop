//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_CUSTOMER_H
#define PROJECT2_CUSTOMER_H

#include "Person.h"

// inherits from the Person class
class Customer : public Person {
  // arrivalTime, orderDuration, brewDuration, price of the order, finish time of the brewing declarations
  double arrival, order, brew, price, finish;
public:
  // constructor for the person => arrival, order, brew, price
  Customer(double, double, double, double);

  // returns the arrival time
  double getArrival();

  // returns the order duration
  double getOrder();

  // returns the brew duration
  double getBrew();

  // returns the price of the order
  double getPrice();

  // sets the finish time, used when the brewing is finished.
  void setFinish(double);

  // returns the turnaround duration, which is (finish time - arrival time)
  double getTurnaround();
};


#endif //PROJECT2_CUSTOMER_H
