//
// Created by corupta on 08.11.2017.
//

#include <bits/stdc++.h>

using namespace std;

// I tried to make this program as OOP as possible, for clarity and for fun.
// I believe reading the comments in main only is enough to understand the whole mechanism,
// so I'd suggest reading other classes only to check out my implementations of those classes.
// I mean, there's no need to check out other classes before understanding this main file.
#include "People/Customer.h"
#include "People/Cashier.h"
#include "People/Barista.h"
#include "Queues/EventQueue.h"
#include "Queues/OrderQueue.h"
#include "Queues/BrewQueue.h"
#include "IdMinHeap.h"


/*
 * Solution Model 1
 * There is 1 OrderQueue
 * There is 1 BrewQueue
 *
 * takes a file variable as a parameter to print the solution's result,
 * takes the number of cashiers, N
 * takes a customers vector, tries the solution using it, but does not alter the customers vector.
 */
void solutionModel1(FILE *fout, int N, vector<Customer *> &customers) {
  // Event queue is a priority queue, to get the next occuring event, and push new events.
  // Check out its class for more details.
  EventQueue eventQueue;
  for (unsigned int i = 0; i < customers.size(); ++i) {
    // push a new event for each customer's arrival
    eventQueue.pushEvent(customers[i], customers[i]->getArrival());
  }
  // there are N cashiers, and N / 3 baristas
  Cashier cashiers[N];
  Barista baristas[N / 3];
  // IdMinHeap is a Priority Queue, that gives the next available cashier/barista id with the smallest value.
  IdMinHeap readyCashiers, readyBaristas;
  // OrderQueue is a fifo queue for customers, that have arrived and are waiting for a cashier.
  OrderQueue orderQueue;
  // BrewQueue is a priority queue for customers (according to the price of their orders), that have arrived and are waiting for a barista.
  BrewQueue brewQueue;
  // initially, push each employee to the readyCashiers/Baristas queues.
  for (unsigned int i = 0; i < N; ++i) {
    readyCashiers.push(i);
    cashiers[i].setEmployeeId(i);
    if (i < N / 3) {
      readyBaristas.push(i);
      baristas[i].setEmployeeId(i);
    }
  }
  // iterate until all events are done.
  while (!eventQueue.empty()) {
    // simultaneous events happen in this do while block
    do {
      // ###################### AN EVENT STARTS ######################
      // an Employee, and Customer declarations, to be used when needed.
      Employee *employee;
      Customer *currCustomer;
      // get next event
      Event *event = eventQueue.popEvent();
      // get the person of that event.
      Person *person = event->getPerson();

      // get the type of person in the event, to determine what event is it
      // customer means arrival of that customer
      // cashier means that cashier finished an order
      // barista means that barista finished a brew

      if (person->getPersonType() == customer) {
        // ###################### CUSTOMER EVENT STARTS ######################
        // customer arrives
        currCustomer = (Customer *) person;

        // handle cashier event for new customer
        if (readyCashiers.empty()) {
          // there are no ready cashiers
          orderQueue.pushCustomer(currCustomer);
        } else {
          // cashier with the following id is assigned to the customer
          int cashierId = readyCashiers.pop();
          cashiers[cashierId].newCustomer(currCustomer);
          // an event is created for when this cashier finishes the order.
          eventQueue.pushEvent(&cashiers[cashierId], currCustomer->getOrder());
        }
        // ###################### CUSTOMER EVENT ENDS ######################
      } else {
        // ###################### EMPLOYEE EVENT STARTS ######################
        // order or brew finishes

        // person is either a cashier or a barista
        employee = (Employee *) person;

        // currCustomer is the customer assigned to that employee
        currCustomer = employee->getCurrentCustomer();

        if (person->getPersonType() == cashier) {
          // ###################### CASHIER EVENT STARTS ######################
          // a cashier finishes an order

          // handle freed cashier, assign it to a new customer
          if (orderQueue.empty()) {
            // there are no customers waiting in the order queue
            readyCashiers.push((employee->getEmployeeId()));
          } else {
            // assign the cashier to the next customer in the order queue
            Customer *nextCustomer = orderQueue.popCustomer();
            employee->newCustomer(nextCustomer);
            // an event is created for when this cashier finishes the order.
            eventQueue.pushEvent(employee, nextCustomer->getOrder());
          }

          // handle barista event for the customer
          if (readyBaristas.empty()) {
            // there are no ready baristas
            brewQueue.pushCustomer(currCustomer);
          } else {
            // barista with the following id is assigned to the customer
            int baristaId = readyBaristas.pop();
            baristas[baristaId].newCustomer(currCustomer);
            // an event is created for when this barista finishes the brew
            eventQueue.pushEvent(&baristas[baristaId], currCustomer->getBrew());
          }
          // ###################### CASHIER EVENT ENDS ######################
        } else { // person -> getPersonType() == barista
          // ###################### BARISTA EVENT STARTS ######################
          // a barista finishes a brew

          // handle freed barista, assign it to a new customer
          if (brewQueue.empty()) {
            // there are no customers waiting in the brew queue
            readyBaristas.push((employee->getEmployeeId()));
          } else {
            // assign the barista to the next customer in the brew queue
            Customer *nextCustomer = brewQueue.popCustomer();
            employee->newCustomer(nextCustomer);
            // an event is created for when this barista finishes the brew.
            eventQueue.pushEvent(employee, nextCustomer->getBrew());
          }

          // both the order and the brew of the current customer is finished
          // set the finish time of that customer
          currCustomer->setFinish(eventQueue.getCurrentTime());
          // ###################### BARISTA EVENT ENDS ######################
        }
        // ###################### EMPLOYEE EVENT ENDS ######################
      }
      delete event;
      // ######################  AN EVENT ENDS ######################
      // if the next event is simultaneous do the next event also.
    } while (eventQueue.doNextAlso());

    // simultaneous events are completed,
    // check the current length of the order queue and the brew queue.
    orderQueue.updateMaxLen();
    brewQueue.updateMaxLen();
  }
  // all events are finished.

  // print the results of this solution model
  double totalTime = eventQueue.getCurrentTime();
  fprintf(fout, "%.2lf\n", totalTime); // total running time
  fprintf(fout, "%u\n", orderQueue.getMaxLen()); // maximum length of the cashier queue
  fprintf(fout, "%u\n", brewQueue.getMaxLen()); // maximum length of the barista queue
  for (int i = 0; i < N; ++i) {
    fprintf(fout, "%.2lf\n", cashiers[i].getBusyTime() / totalTime); // utilizations of the cashiers
  }
  for (int i = 0; i < N / 3; ++i) {
    fprintf(fout, "%.2lf\n", baristas[i].getBusyTime() / totalTime); // utilization of the baristas
  }
  for (int i = 0; i < customers.size(); ++i) {
    fprintf(fout, "%.2lf\n", customers[i]->getTurnaround()); // turnaround times of orders
  }
}

/*
 * Solution Model 2
 * There is 1 OrderQueue
 * There is N / 3 BrewQueue
 *
 * takes a file variable as a parameter to print the solution's result,
 * takes the number of cashiers, N
 * takes a customers vector, tries the solution using it, but does not alter the customers vector.
 */
void solutionModel2(FILE *fout, int N, vector<Customer *> &customers) {
  // Event queue is a priority queue, to get the next occuring event, and push new events.
  // Check out its class for more details.
  EventQueue eventQueue;
  for (unsigned int i = 0; i < customers.size(); ++i) {
    // push a new event for each customer's arrival
    eventQueue.pushEvent(customers[i], customers[i]->getArrival());
  }
  // there are N cashiers, and N / 3 baristas
  Cashier cashiers[N];
  Barista baristas[N / 3];
  // IdMinHeap is a Priority Queue, that gives the next available cashier/barista id with the smallest value.
  // In this solution model, there can be only 1 id in each readyBaristas queue,
  // because each baristas assigned to the customers coming from 3 specific cashiers.
  // (except the last barista who is assigned to customers coming from 1 specific cashier)
  IdMinHeap readyCashiers, readyBaristas[N / 3];
  // OrderQueue is a fifo queue for customers, that have arrived and are waiting for a cashier.
  OrderQueue orderQueue;
  // BrewQueue is a priority queue for customers (according to the price of their orders), that have arrived and are waiting for a barista.
  // There are N / 3 brew queues, for each barista in this solution model.
  BrewQueue brewQueue[N / 3];
  // initially, push each employee to the readyCashiers/Baristas queues.
  for (unsigned int i = 0; i < N; ++i) {
    readyCashiers.push(i);
    cashiers[i].setEmployeeId(i);
    if (i < N / 3) {
      readyBaristas[i].push(i);
      baristas[i].setEmployeeId(i);
    }
  }
  // iterate until all events are done.
  while (!eventQueue.empty()) {
    // simultaneous events happen in this do while block
    do {
      // ###################### AN EVENT STARTS ######################
      // an Employee, and Customer declarations, to be used when needed.
      Employee *employee;
      Customer *currCustomer;
      // get next event
      Event *event = eventQueue.popEvent();
      // get the person of that event.
      Person *person = event->getPerson();

      // get the type of person in the event, to determine what event is it
      // customer means arrival of that customer
      // cashier means that cashier finished an order
      // barista means that barista finished a brew

      if (person->getPersonType() == customer) {
        // ###################### CUSTOMER EVENT STARTS ######################
        // customer arrives
        currCustomer = (Customer *) person;

        // handle cashier event for new customer
        if (readyCashiers.empty()) {
          // there are no ready cashiers
          orderQueue.pushCustomer(currCustomer);
        } else {
          // cashier with the following id is assigned to the customer
          int cashierId = readyCashiers.pop();
          cashiers[cashierId].newCustomer(currCustomer);
          // an event is created for when this cashier finishes the order.
          eventQueue.pushEvent(&cashiers[cashierId], currCustomer->getOrder());
        }
        // ###################### CUSTOMER EVENT ENDS ######################
      } else {
        // ###################### EMPLOYEE EVENT STARTS ######################
        // order or brew finishes

        // person is either a cashier or a barista
        employee = (Employee *) person;

        // currCustomer is the customer assigned to that employee
        currCustomer = employee->getCurrentCustomer();

        if (person->getPersonType() == cashier) {
          // ###################### CASHIER EVENT STARTS ######################
          // a cashier finishes an order

          // handle freed cashier, assign it to a new customer
          if (orderQueue.empty()) {
            // there are no customers waiting in the order queue
            readyCashiers.push((employee->getEmployeeId()));
          } else {
            // assign the cashier to the next customer in the order queue
            Customer *nextCustomer = orderQueue.popCustomer();
            employee->newCustomer(nextCustomer);
            // an event is created for when this cashier finishes the order.
            eventQueue.pushEvent(employee, nextCustomer->getOrder());
          }

          // get the id of barista queue for the customer which is the cashier id / 3
          unsigned int baristaQueueId = (employee->getEmployeeId()) / 3;

          // handle barista event for the customer
          if (readyBaristas[baristaQueueId].empty()) {
            // there are no ready baristas with that id. (the barista with that id is not available)
            brewQueue[baristaQueueId].pushCustomer(currCustomer);
          } else {
            // barista with the following id is assigned to the customer
            int baristaId = readyBaristas[baristaQueueId].pop();
            baristas[baristaId].newCustomer(currCustomer);
            // an event is created for when this barista finishes the brew
            eventQueue.pushEvent(&baristas[baristaId], currCustomer->getBrew());
          }
          // ###################### CASHIER EVENT ENDS ######################
        } else { // person -> getPersonType() == barista
          /// ###################### BARISTA EVENT STARTS ######################
          // a barista finishes a brew

          // get the id of that barista
          unsigned int baristaQueueId = employee->getEmployeeId();

          // handle freed barista, assign it to a new customer
          if (brewQueue[baristaQueueId].empty()) {
            // there are no customers waiting in the brew queue
            readyBaristas[baristaQueueId].push((employee->getEmployeeId()));
          } else {
            // assign the barista to the next customer in the related brew queue
            Customer *nextCustomer = brewQueue[baristaQueueId].popCustomer();
            employee->newCustomer(nextCustomer);
            // an event is created for when this barista finishes the brew.
            eventQueue.pushEvent(employee, nextCustomer->getBrew());
          }

          // both the order and the brew of the current customer is finished
          // set the finish time of that customer
          currCustomer->setFinish(eventQueue.getCurrentTime());
          // ###################### BARISTA EVENT ENDS ######################
        }
        // ###################### EMPLOYEE EVENT ENDS ######################
      }
      delete event;
      // ######################  AN EVENT ENDS ######################
      // if the next event is simultaneous do the next event also.
    } while (eventQueue.doNextAlso());

    // simultaneous events are completed,
    // check the current length of the order queue and the brew queues.
    orderQueue.updateMaxLen();
    for (int i = 0; i < N / 3; ++i) {
      brewQueue[i].updateMaxLen();
    }
  }
  // all events are finished.

  // print the results of this solution model
  double totalTime = eventQueue.getCurrentTime();
  fprintf(fout, "%.2lf\n", totalTime); // total running time
  fprintf(fout, "%u\n", orderQueue.getMaxLen()); // maximum length of the cashier queue
  for (int i = 0; i < N / 3; ++i) {
    fprintf(fout, "%u\n", brewQueue[i].getMaxLen()); // maximum length of the barista queue
  }
  for (int i = 0; i < N; ++i) {
    fprintf(fout, "%.2lf\n", cashiers[i].getBusyTime() / totalTime); // utilizations of the cashiers
  }
  for (int i = 0; i < N / 3; ++i) {
    fprintf(fout, "%.2lf\n", baristas[i].getBusyTime() / totalTime); // utilization of the baristas
  }
  for (int i = 0; i < customers.size(); ++i) {
    fprintf(fout, "%.2lf\n", customers[i]->getTurnaround()); // turnaround times of orders
  }
}


int main(int argc, char *argv[]) {

  // check argc & argv
  if (argc != 3) {
    cout << "Run the code with the following command: ./project2 [input_file] [output_file]" << endl;
    return 1;
  }

  // open filestreams
  ifstream infile(argv[1]);
  FILE *fout = fopen(argv[2], "w");

  // definitions N is number of cashiers, m is number of customers
  int N, m;
  double arrival, order, brew, price;
  vector<Customer *> customers;

  // read input: N, m and customer data
  infile >> N >> m;
  while (m--) {
    infile >> arrival >> order >> brew >> price;
    customers.push_back(new Customer(arrival, order, brew, price));
  }

  // try the solution model 1, print its results.
  solutionModel1(fout, N, customers);
  // print an endline between the solutions
  fprintf(fout, "\n");
  // try the solution model 2, print its results.
  solutionModel2(fout, N, customers);

  // close filestreams
  infile.close();
  fclose(fout);
}
