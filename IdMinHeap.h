//
// Created by corupta on 09.11.2017.
//

#ifndef PROJECT2_IDMINHEAP_H
#define PROJECT2_IDMINHEAP_H

#include <queue>

using namespace std;

class IdMinHeap {
  priority_queue<unsigned int, vector<unsigned int>, greater<unsigned int> > queue;
public:
  IdMinHeap();

  void push(unsigned int);

  unsigned int pop();

  bool empty();

};


#endif //PROJECT2_IDMINHEAP_H
