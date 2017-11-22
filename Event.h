//
// Created by corupta on 08.11.2017.
//


#ifndef PROJECT2_EVENT_H
#define PROJECT2_EVENT_H

#include "People/Person.h"

class Event {

  // at which time the event happens
  double triggerTime;

  // the main person related to that event
  Person *person;
  /*
   * if the person is a customer, event is the arrival of that customer
   * if the person is a cashier, event is the cashier finishing an order
   * if the person is a barista, event is the barista finishing a brew
   *
   * thus, the event type can be determined via the type of the person.
   */

public:
  // constructor, that takes the person and the triggerTime
  Event(Person *, double);

  // returns the triggerTime
  double getTime();

  // returns the related person
  Person *getPerson();
};


#endif //PROJECT2_EVENT_H
