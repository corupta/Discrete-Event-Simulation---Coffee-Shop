//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EMPLOYEE_H
#define PROJECT2_EMPLOYEE_H

#include "Customer.h"

// inherits from the Person class
class Employee : public Person {
protected:
  // the customer assigned last to the current employee
  Customer *currentCustomer;

  // the id of the employee, used to get the id of the employee in the array it was created
  unsigned int employeeId;

  // starts from 0, the sum of all event durations of that employee.
  // for cashiers: the time spent for orders
  // for baristas: the time spent for brewing.
  double busyTime;
public:
  // constructor that sets the person type
  explicit Employee(PersonType);

  // sets the employee id
  void setEmployeeId(unsigned int);

  // get the employee id
  unsigned int getEmployeeId();

  // get the current customer
  Customer *getCurrentCustomer();

  // used to update busyTime and assign a customer to the employee
  virtual void newCustomer(Customer *) = 0; // pure virtual

  // returns the busy time
  double getBusyTime();
};


#endif //PROJECT2_EMPLOYEE_H
