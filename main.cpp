//
// Created by corupta on 08.11.2017.
//

// todo fix read & write file

#include <bits/stdc++.h>

using namespace std;

#include "People/Customer.h"
#include "People/Cashier.h"
#include "People/Barista.h"
#include "Queues/EventQueue.h"
#include "Queues/OrderQueue.h"
#include "Queues/BrewQueue.h"
#include "IdMinHeap.h"


/*
 * 1 OrderQueue
 * 1 BrewQueue
 */
void solutionModel1(ostream &os, int N, vector<Customer *> & customers) {
  EventQueue eventQueue;
  for (unsigned int i = 0; i < customers.size(); ++i) {
    eventQueue.pushEvent(customers[i], customers[i]->getArrival());
  }
  Cashier cashiers[N];
  Barista baristas[N / 3];
  IdMinHeap readyCashiers, readyBaristas;
  OrderQueue orderQueue;
  BrewQueue brewQueue;
  for (unsigned int i = 0; i < N; ++i) {
    readyCashiers.push(i);
    cashiers[i].setEmployeeId(i);
    if (i < N / 3) {
      readyBaristas.push(i);
      baristas[i].setEmployeeId(i);
    }
  }
  while (!eventQueue.empty()) {
    //cerr << "outside loop starts" << endl;
    do {
      //cerr << "inner loop starts" << endl;
      //eventQueue.dumpShit();
      Event *event = eventQueue.popEvent();
      //eventQueue.dumpShit();
      Person *person = event->getPerson();
      Employee * employee;
      Customer* currCustomer;
      if (person -> getPersonType() == customer) {
        // customer arrives
        //cerr << "customer arrives" << endl;
        currCustomer = (Customer*)person;

        // handle cashier event
        if (readyCashiers.empty()) {
          orderQueue.pushCustomer(currCustomer);
        } else {
          int cashierId = readyCashiers.pop();
          cashiers[cashierId].newCustomer(currCustomer);
          eventQueue.pushEvent(&cashiers[cashierId], currCustomer -> getOrder());
        }
      } else {
        // order or brew finishes
        employee = (Employee *)person;
        currCustomer = employee -> getCurrentCustomer();

        if (person -> getPersonType() == cashier) {
          // order finishes
          //cerr << "order finishes" << endl;

          // handle cashier
          if (orderQueue.empty()) {
            readyCashiers.push((employee -> getEmployeeId()));
          } else {
            Customer* nextCustomer = orderQueue.popCustomer();
            employee -> newCustomer(nextCustomer);
            eventQueue.pushEvent(employee, nextCustomer -> getOrder());
          }

          // handle barista event
          if (readyBaristas.empty()) {
            brewQueue.pushCustomer(currCustomer);
          } else {
            int baristaId = readyBaristas.pop();
            baristas[baristaId].newCustomer(currCustomer);
            eventQueue.pushEvent(&baristas[baristaId], currCustomer -> getBrew());
          }
        } else { // person -> getPersonType() == barista
          // brew finishes
          //cerr << "brew finishes" << endl;
          // handle barista
          if (brewQueue.empty()) {
            readyBaristas.push((employee->getEmployeeId()));
          } else {
            Customer* nextCustomer = brewQueue.popCustomer();
            employee -> newCustomer(nextCustomer);
            eventQueue.pushEvent(employee, nextCustomer -> getBrew());
          }

          // handle finish event
          currCustomer -> setFinish(eventQueue.getCurrentTime());
        }
      }
      delete event;
    } while (eventQueue.doNextAlso());
    //cerr << "inner loop ends" << endl;
    orderQueue.updateMaxLen();
    brewQueue.updateMaxLen();
  }
  //cerr << "outer loop ends" << endl;
  double totalTime = eventQueue.getCurrentTime();
  printf("%.2lf\n", totalTime); // total running time
  printf("%u\n", orderQueue.getMaxLen()); // maximum length of the cashier queue
  printf("%u\n", brewQueue.getMaxLen()); // maximum length of the barista queue
  for (int i = 0; i < N; ++i) {
    printf("%.2lf\n", cashiers[i].getBusyTime() / totalTime); // utilizations of the cashiers
  }
  for (int i = 0; i < N / 3; ++i) {
    printf("%.2lf\n", baristas[i].getBusyTime() / totalTime); // utilization of the baristas
  }
  for (int i = 0; i < customers.size(); ++i) {
    printf("%.2lf\n", customers[i]->getTurnaround()); // turnaround times of orders
  }
}

// 1 OrderQueue
// N/3 BreqQueue
void solutionModel2(ostream &os, int N, vector<Customer *> & customers) {
  EventQueue eventQueue;
  for (unsigned int i = 0; i < customers.size(); ++i) {
    eventQueue.pushEvent(customers[i], customers[i]->getArrival());
  }
  Cashier cashiers[N];
  Barista baristas[N / 3];
  IdMinHeap readyCashiers, readyBaristas[N / 3];
  OrderQueue orderQueue;
  BrewQueue brewQueue[N / 3];
  for (unsigned int i = 0; i < N; ++i) {
    readyCashiers.push(i);
    cashiers[i].setEmployeeId(i);
    if (i < N / 3) {
      readyBaristas[i].push(i);
      baristas[i].setEmployeeId(i);
    }
  }
  while (!eventQueue.empty()) {
    //cerr << "outside loop starts" << endl;
    do {
      //cerr << "inner loop starts" << endl;
      //eventQueue.dumpShit();
      Event *event = eventQueue.popEvent();
      //eventQueue.dumpShit();
      Person *person = event->getPerson();
      Employee * employee;
      Customer* currCustomer;
      if (person -> getPersonType() == customer) {
        // customer arrives
        //cerr << "customer arrives" << endl;
        currCustomer = (Customer*)person;

        // handle cashier event
        if (readyCashiers.empty()) {
          orderQueue.pushCustomer(currCustomer);
        } else {
          int cashierId = readyCashiers.pop();
          cashiers[cashierId].newCustomer(currCustomer);
          eventQueue.pushEvent(&cashiers[cashierId], currCustomer -> getOrder());
        }
      } else {
        // order or brew finishes
        employee = (Employee *)person;
        currCustomer = employee -> getCurrentCustomer();

        if (person -> getPersonType() == cashier) {
          // order finishes
          //cerr << "order finishes" << endl;

          // handle cashier
          if (orderQueue.empty()) {
            readyCashiers.push((employee -> getEmployeeId()));
          } else {
            Customer* nextCustomer = orderQueue.popCustomer();
            employee -> newCustomer(nextCustomer);
            eventQueue.pushEvent(employee, nextCustomer -> getOrder());
          }

          // get id of barista queue
          unsigned int baristaQueueId = (employee -> getEmployeeId()) / 3;

          // handle barista event
          if (readyBaristas[baristaQueueId].empty()) {
            brewQueue[baristaQueueId].pushCustomer(currCustomer);
          } else {
            int baristaId = readyBaristas[baristaQueueId].pop();
            baristas[baristaId].newCustomer(currCustomer);
            eventQueue.pushEvent(&baristas[baristaId], currCustomer -> getBrew());
          }
        } else { // person -> getPersonType() == barista
          // brew finishes;

          // get id of barista queue
          unsigned int baristaQueueId = employee -> getEmployeeId();

          // handle barista
          if (brewQueue[baristaQueueId].empty()) {
            readyBaristas[baristaQueueId].push((employee->getEmployeeId()));
          } else {
            Customer* nextCustomer = brewQueue[baristaQueueId].popCustomer();
            employee -> newCustomer(nextCustomer);
            eventQueue.pushEvent(employee, nextCustomer -> getBrew());
          }

          // handle finish event
          currCustomer -> setFinish(eventQueue.getCurrentTime());
        }
      }
      delete event;
    } while (eventQueue.doNextAlso());
    //cerr << "inner loop ends" << endl;
    orderQueue.updateMaxLen();
    for (int i = 0; i < N / 3; ++i) {
      brewQueue[i].updateMaxLen();
    }
  }
  //cerr << "outer loop ends" << endl;
  double totalTime = eventQueue.getCurrentTime();
  printf("%.2lf\n", totalTime); // total running time
  printf("%u\n", orderQueue.getMaxLen()); // maximum length of the cashier queue
  for (int i = 0; i < N / 3; ++i) {
    printf("%u\n", brewQueue[i].getMaxLen()); // maximum length of the barista queue
  }
  for (int i = 0; i < N; ++i) {
    printf("%.2lf\n", cashiers[i].getBusyTime() / totalTime); // utilizations of the cashiers
  }
  for (int i = 0; i < N / 3; ++i) {
    printf("%.2lf\n", baristas[i].getBusyTime() / totalTime); // utilization of the baristas
  }
  for (int i = 0; i < customers.size(); ++i) {
    printf("%.2lf\n", customers[i]->getTurnaround()); // turnaround times of orders
  }
}


int main() {
  int N, m;
  double arrival, order, brew, price;
  cin >> N >> m;
  vector<Customer*> customers;
  while (m--) {
    cin >> arrival >> order >> brew >> price;
    customers.push_back(new Customer(arrival, order, brew, price));
  }
  solutionModel1(cout, N, customers);
  cout << endl;
  solutionModel2(cout, N, customers);
  // Customer a;
}


/*


 sample input

6
10
0 20.75 24.89 10.30
3.21 22.47 18.12 7.57
5.17 19.83 32.35 13.93
8.16 21.10 11.32 25.95
9.54 26.05 17.14 8.15
10.32 11.10 14.08 3.74
16.47 34.68 41.41 16.98
23.13 17.33 16.22 9.86
27.52 40.68 23.43 20.97
28.08 16.80 30.47 11.32


 sample output

137.52
1
5
0.40
0.46
0.27
0.15
0.19
0.21
0.85
0.82
45.64
134.31
72.82
38.66
124.54
25.18
102.93
93.81
73.20
49.21

191.42
1
4
2
0.29
0.33
0.19
0.11
0.14
0.15
0.89
0.31
45.64
188.21
72.82
38.66
70.64
25.18
126.36
39.91
73.90
145.22

 */