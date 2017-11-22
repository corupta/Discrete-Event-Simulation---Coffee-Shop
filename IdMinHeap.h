//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_IDMINHEAP_H
#define PROJECT2_IDMINHEAP_H

#include <queue>

using namespace std;

class IdMinHeap {
  // a priority queue, but a min heap instead of a max heap
  priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > queue;

public:
  IdMinHeap();

  // push an id to the priority queue
  void push(unsigned int);

  // pop and return the id at the top of the priority queue
  unsigned int pop();

  // returns true if the priority queue is empty.
  bool empty();

};


#endif //PROJECT2_IDMINHEAP_H
