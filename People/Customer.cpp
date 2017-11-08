//
// Created by corupta on 08.11.2017.
//
#include <bits/stdc++.h>
#include "Customer.h"

Customer::Customer(double arrival, double order, double brew, double price) :
    Person(customer), arrival(arrival), order(order), brew(brew), price(price) {}

double Customer::getArrival() {
  return arrival;
};

double Customer::getOrder() {
  return order;
};

double Customer::getBrew() {
  return brew;
};

double Customer::getPrice() {
  return price;
};

void Customer::setFinish(double newFinish) {
  finish = newFinish;
};

double Customer::getTurnaround() {
  return finish - arrival;
};