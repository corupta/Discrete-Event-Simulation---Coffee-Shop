//
// Created by corupta on 08.11.2017.
//

#include "EventQueue.h"

#define EPSILON (1.0E-8)

EventQueue::EventQueue() : currentTime(0) {}

bool EventQueue::Compare::operator()(Event *a, Event *b) {
  // return true if a should happen later (time is bigger, or id)
  if (a->getTime() == b->getTime()) {
    return a->getPerson()->getId() > b->getPerson()->getId();
  }
  return a->getTime() > b->getTime();
}

void EventQueue::pushEvent(Person *person, double time) {
  Event *event = new Event(person, time);
  queue.push(event);
}

Event *EventQueue::popEvent() {
  Event *event = queue.top();
  currentTime = event->getTime();
  queue.pop();
  return event;
}

bool EventQueue::doNextAlso() {
  if (!queue.empty()) {
    double nextTime = queue.top()->getTime();
    if (nextTime + EPSILON > currentTime && nextTime < currentTime + EPSILON) {
      return true;
    }
  }
  return false;
}

bool EventQueue::empty() {
  return queue.empty();
}