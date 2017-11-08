//
// Created by corupta on 08.11.2017.
//

#include "Event.h"

Event::Event(Person *person, double triggerTime) : triggerTime(triggerTime), person(person) {}

double Event::getTime() {
  return triggerTime;
}

Person *Event::getPerson() {
  return person;
}
