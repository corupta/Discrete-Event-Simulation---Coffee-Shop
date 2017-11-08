//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EVENTQUEUE_H
#define PROJECT2_EVENTQUEUE_H

#include "Event.h"
#include <queue>

using namespace std;

class EventQueue {
  class Compare {
  public:
    bool operator()(Event *, Event *);
  };

  priority_queue<Event *, vector<Event *>, Compare> queue;
  double currentTime;
public:
  EventQueue();

  void pushEvent(Person *, double);

  Event *popEvent();

  // next event is simultaneous
  bool doNextAlso();

  bool empty();
};


#endif //PROJECT2_EVENTQUEUE_H
