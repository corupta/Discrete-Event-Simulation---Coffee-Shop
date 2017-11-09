//
// Created by corupta on 08.11.2017.
//

#ifndef PROJECT2_EVENTQUEUE_H
#define PROJECT2_EVENTQUEUE_H

#include "../Event.h"
#include <queue>

using namespace std;

class EventQueue {
  class CompareEvent {
  public:
    bool operator()(Event *, Event *);
  };

  priority_queue<Event *, vector<Event *>, CompareEvent> eventQueue;
  double currentTime;
public:
  EventQueue();

  void pushEvent(Person *, double);

  Event *popEvent();

  double getCurrentTime();

  // next event is simultaneous
  bool doNextAlso();

  bool empty();

  void dumpShit();
};


#endif //PROJECT2_EVENTQUEUE_H
