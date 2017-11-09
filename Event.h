//
// Created by corupta on 08.11.2017.
//


#ifndef PROJECT2_EVENT_H
#define PROJECT2_EVENT_H

#include "People/Person.h"

class Event {
  double triggerTime;
  Person *person;
public:
  Event(Person *, double);

  double getTime();

  Person *getPerson();
};


#endif //PROJECT2_EVENT_H
