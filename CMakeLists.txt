cmake_minimum_required(VERSION 2.8)
project(project2)

set(CMAKE_CXX_STANDARD 11)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp People/Customer.cpp People/Customer.h Event.cpp Event.h People/Person.cpp People/Person.h People/Cashier.cpp People/Cashier.h People/Barista.cpp People/Barista.h People/Employee.cpp People/Employee.h EventQueue.cpp EventQueue.h)
add_executable(project2 ${SOURCE_FILES})