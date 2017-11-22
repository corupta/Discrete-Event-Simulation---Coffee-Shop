//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_PERSON_H
#define PROJECT2_PERSON_H

enum PersonType {
  customer, cashier, barista
};
// enumeration to specify PersonType

class Person {
  // an id that increases with each new person created.
  static unsigned int increasingId;

  // increasingId is assigned as the comparisonId of the each newly created person.
  // then, the comparisonId is used to sort cashiers & baristas in the event queue, in order to get the person with the smallest id when some events are simultaneous.
  // customers are created first, cashiers are next, and baristas are last.
  // (customers have the smallest ids, then cashiers, then baristas.)
  // thus, for simultaneous events of each, the customer arrivals will be the first events checked,
  // cashiers' order finishes will be the second events checked.
  // baristas' brew finishes will be the last events checked.
  // that way, when a cashier finishes an order and checks the orderqueue, it's made sure that no other simultaneous customer arrival will happen. (order queue is final for that moment)
  // similarly, when a barista finishes an order and checks the brewqueue, it's made sure that no other simultaneous order finishes will happen.  (brew queue is final for that moment)
  // additionally, free cashiers with lower ids must serve before others, when there are other free cashiers, also.
  // similaryly, free baristas with lower ids must serve before others, when there are other free baristas, also.
  unsigned int comparisonId;

  // specify whether the person is a customer, cashier or barista.
  PersonType personType;

public:

  // constructor that sets the id and the personType
  Person(PersonType);

  // returns the person type
  int getPersonType();

  // returns the comparisonId
  unsigned int getComparisonId();
};


#endif //PROJECT2_PERSON_H
