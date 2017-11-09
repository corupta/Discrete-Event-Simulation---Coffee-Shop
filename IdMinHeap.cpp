//
// Created by corupta on 09.11.2017.
//

#include "IdMinHeap.h"

IdMinHeap::IdMinHeap() {}

void IdMinHeap::push(unsigned int id) {
  queue.push(id);
}

unsigned int IdMinHeap::pop() {
  unsigned int id = queue.top();
  queue.pop();
  return id;
}

bool IdMinHeap::empty() {
  return queue.empty();
}