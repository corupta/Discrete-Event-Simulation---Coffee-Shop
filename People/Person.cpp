//
// Created by corupta on 08.11.2017.
//

#include "Person.h"

unsigned int Person::increasingId = 0;

Person::Person(PersonType personType) : personType(personType) {
  comparisonId = increasingId++;
}

int Person::getPersonType() {
  return personType;
}

unsigned int Person::getComparisonId() {
  return comparisonId;
}