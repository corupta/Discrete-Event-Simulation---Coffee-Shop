//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EVENTQUEUE_H
#define PROJECT2_EVENTQUEUE_H

#include "../Event.h"
#include <queue>

using namespace std;

// used to determine whether two doubles are equal
// it is assumed that the doubles are equal if the absolute value of their difference is less than EPSILON (a tiny number)
#define EPSILON (1.0E-8)

class EventQueue {
  // takes two time parameters as double, return true if the two double are equal using the EPSILON, which means the times given are simultaneous
  static bool eventsAreSimultaneous(double, double);

  // a comparetor to order events from the earliest occuring the last occuring, but
  // simultaneous events (determined with the eventsAreSimultaneous method, above) are ordered from the lowest person id to the highest, for the person related to that event.
  class CompareEvent {
  public:
    bool operator()(Event *, Event *);
  };

  // priority queue used to push events and to pop the next occuring one.
  priority_queue<Event *, vector<Event *>, CompareEvent> eventQueue;

  // current time in the event queue (the time of the last occured event), initially 0
  double currentTime;

public:

  // a constructor that sets the currentTime to 0.
  EventQueue();

  // takes a person and a duration value as parameters,
  // creates a new event with the given person and a calculated triggerTime (duration + currentTime) for that event,
  // pushes that event to the priority queue
  void pushEvent(Person *, double);

  // pops and returns the next occurring event (the event at the top of the priority queue)
  // also updates the current time.
  Event *popEvent();
  // NOTE: the returned event must be deleted after being used, to avoid memory leak

  // returns the current time
  double getCurrentTime();

  // returns true if the next occurring event is simultaneous (the event at the top of the priority queue)
  bool doNextAlso();

  // returns true if the priority queue is empty
  bool empty();

};


#endif //PROJECT2_EVENTQUEUE_H
