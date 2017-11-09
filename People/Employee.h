//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EMPLOYEE_H
#define PROJECT2_EMPLOYEE_H

#include "Customer.h"

class Employee : public Person {
protected:
  Customer *currentCustomer;
  unsigned int employeeId;
  double busyTime;
public:
  explicit Employee(PersonType);

  void setEmployeeId(unsigned int);

  unsigned int getEmployeeId();

  Customer *getCurrentCustomer();

  virtual void newCustomer(Customer *) = 0; // pure virtual

  double getBusyTime();
};


#endif //PROJECT2_EMPLOYEE_H
