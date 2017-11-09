//
// Created by corupta on 08.11.2017.
//

#include "EventQueue.h"

#define EPSILON (1.0E-8)

EventQueue::EventQueue() : currentTime(0) {}

bool EventQueue::CompareEvent::operator()(Event *a, Event *b) {
  // return true if a should happen later (time is bigger, or id)
  if (a->getTime() == b->getTime()) {
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
    if (nextTime + EPSILON > currentTime && nextTime < currentTime + EPSILON) {
      return true;
    }
  }
  return false;
}

bool EventQueue::empty() {
  return eventQueue.empty();
}

using namespace std;
#include <iostream>
void EventQueue::dumpShit() {
  cerr << "Dump EventQueue: Time(" << currentTime << ") currentSize(" << eventQueue.size() << ")" << endl;
}