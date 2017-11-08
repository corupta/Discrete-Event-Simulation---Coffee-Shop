//
// Created by corupta on 08.11.2017.
//

#include "Person.h"

Person::Person(PersonType personType) : personType(personType) {
  id = increasingId++;
}

int Person::getPersonType() {
  return personType;
}

unsigned int Person::getId() {
  return id;
}