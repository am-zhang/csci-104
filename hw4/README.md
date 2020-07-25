HW4 consists of three main files that can be compiled and run:  
rem_dup.cpp  
deque_test.cpp  
laundry.cpp  

rem_dup_lib.h and rem_dup_lib.cpp  
This program reads two lists of integers specified in a text file with integers separated by spaces on two lines (and only two lines) of the file into two singly linked lists. Recursion is used to:  
1. Recursively remove consecutive integers that are equal from the first list (only keeping one)  
2. Makes a new list (i.e. copying the items in the list) such that the new list contains the concatenation of the first and second list using recursion  

Each of the two operations above are implemented as separate recursive functions that do not contain any loops.

rem_dup.cpp  
This program reads in the integers into the two lists, calls removeDuplicates on the 1st list and then calls concatenate on the resulting 1st and original 2nd list. No STL structures are used in this program.

deque.h  
Defines a Deque<T> templated class in deque.h. This Deque<T> class dynamically resizes when it becomes full. The addition of new items runs in amortized constant runtime. 
  
Deque_test.cpp  
Creates a GTest-based test driver for the Deque<T> class. 
  
stack.h  
Implements a templated Stack class that inherits privately from Deque<T>. All operations run in (amortized) O(1) time. 
  
laundry.cpp  
Consider a gym with white and black towels which patrons discard into a can and employees come and collect some number of towels to wash from the top of the pile. Given a file whose contents record the sequence in which towels are discarded along with when and how many towels the employee picks up to wash, this program outputs the sequence of towels the employee picks up to wash each time he visits the can.  
The input file consists of integers separated by spaces. 0 = black towel, -1 = white towel, and any positive number bigger than 0 represents the employee collecting that many towels from the top of the pile. If there are less towels than the employee tries to pick up, he will just get the available towels.  
This program uses the templated Stack class in its implementation. It runs in O(n) where n is the number of integers in the input file.

They can be compiled by entering _make_ at the command line.  

A sample invocation of remdup would be:  
./remdup input.txt output.txt  

A sample invocation of laundry would be:  
./laundry laundry.in laundry.out  

laundry.cpp relies on a templated Stack class which can be found in stack.h.  
This class inherits privately from a templated Deque class which can be found in deque.h.  
deque_test.cpp, a gtest-based test driver for the templated Deque class, can be run by entering _make_ at the command line.

Please check the comments in the above programs for any clarifications.
