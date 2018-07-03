# Discrete-Event Simulation - Coffee Shop
### C++ Project to create a sample discrete event simulation

## Project Details

That's a project I've created as a university homework for the course, CMPE 250 - Data Structures and Algorithms on April 22nd, 2018.

What the project is about can be found via [Project2.pdf](https://github.com/corupta/Discrete-Event-Simulation---Coffee-Shop/blob/master/Project2.pdf)

## My Solution

I tried to make this program as OOP as possible, for clarity and for fun.

I believe reading the comments in main only is enough to understand the whole mechanism,
so I'd suggest reading other classes only to check out my implementations of those classes.

I mean, there's no need to check out other classes before understanding this main file.

Below is an overview of those classes:

#### People
* Person is a base class.
    * Employee inherits from the Person
        * Cashier inherits from the Employee
        * Barista inherits from the Employee
    * Customer inherits from the Person

#### Event is either customer arrives, cashier finishes order, or barista finishes brew.
Event is a class with one Person and one triggerTime.
* if the person is of type customer => event is customer arrives.
* if the person is of type cashier => event is cashier finishes order.
* if the person is of type barista => event is barista finishes brew.

#### Queues
* OrderQueue for customers waiting for order
* BrewQueue for customers waiting for brew
* EventQueue to detect next occuring event.

#### IdMinHeap is just a priority queue in reverse direction (minheap instead of maxheap)
Used to determine, which available cashier/barista has the lowest id.


#### _Tried & Committed Test Cases sent via mail._

Note: the test cases have windows endlines(\r\n) but my program puts linux endlines in the output(\n),
except for that outputs in the sample tests were identical to my outputs.

- - - -


# CMPE250_2017Fall_Project2

Due date: 23.11.2017 23:59

Please check out Project2.pdf for description of the project.

Due date is a strict due date!

## How to compile

In a terminal, call commands:
```
>cmake CMakeLists.txt

>make

OR

>cmake CMakeLists.txt && make

```
Make sure the executable is produced.

Then you can test the project with the command:
```
>./project2 inputFile outputFile
```
