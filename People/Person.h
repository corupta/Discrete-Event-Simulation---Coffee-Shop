//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_PERSON_H
#define PROJECT2_PERSON_H

enum PersonType {
  customer, cashier, barista
};

class Person {
  static unsigned int increasingId = 0;
  PersonType personType;
  unsigned int id;
public:
  Person(PersonType);

  int getPersonType();

  unsigned int getId();
};


#endif //PROJECT2_PERSON_H
