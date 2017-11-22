//
// Created by corupta on 08.11.2017.
//

#include "EventQueue.h"

EventQueue::EventQueue() : currentTime(0) {}

bool EventQueue::eventsAreSimultaneous(double timeA, double timeB) {
  return (timeA + EPSILON > timeB && timeA < timeB + EPSILON);
}

bool EventQueue::CompareEvent::operator()(Event *a, Event *b) {
  // return true if a should happen later (time is bigger, or id)
  if (eventsAreSimultaneous(a->getTime(), b->getTime())) {
    return a->getPerson()->getComparisonId() > b->getPerson()->getComparisonId();
  }
  return a->getTime() > b->getTime();
}

void EventQueue::pushEvent(Person *person, double time) {
  Event *event = new Event(person, currentTime + time);
  eventQueue.push(event);
}

Event *EventQueue::popEvent() {
  Event *event = eventQueue.top();
  currentTime = event->getTime();
  eventQueue.pop();
  return event;
}

double EventQueue::getCurrentTime() {
  return currentTime;
}


bool EventQueue::doNextAlso() {
  if (!eventQueue.empty()) {
    double nextTime = eventQueue.top()->getTime();
    return eventsAreSimultaneous(currentTime, nextTime);
  }
  return false;
}

bool EventQueue::empty() {
  return eventQueue.empty();
}
