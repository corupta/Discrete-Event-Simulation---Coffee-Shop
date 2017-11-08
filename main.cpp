//
// Created by corupta on 08.11.2017.
//
#include <bits/stdc++.h>

using namespace std;

#include "People/Customer.h"
#include "People/Cashier.h"
#include "People/Barista.h"
#include "EventQueue.h"


//todo
void solutionModel1(ofstream &os, int N, vector<Customer *> customers) {
  EventQueue eventQueue;
  for (int i = 0; i < customers.size(); ++i) {
    eventQueue.pushEvent(customers[i], customers[i]->getArrival());
  }
  Cashier cashiers[N];
  Barista baristas[N / 3];
  set<int> readyCashiers, readyBaristas;
  for (int i = 0; i < N; ++i) {
    readyCashiers.insert(i);
    if (i < N / 3) {
      readyBaristas.insert(i);
    }
  }
  while (!eventQueue.empty()) {
    do {
      Event *event = eventQueue.popEvent();
      Person *person = event->getPerson();
      switch (person->getPersonType()) {
        case customer:

          break;
        case cashier:
          break;
        case barista:
          break;
      }

    } while (eventQueue.doNextAlso());
  }
}

int main() {
  printf("Hello World");
  // Customer a;
}