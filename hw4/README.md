HW4 consists of two main files that can be compiled and run:  
rem_dup.cpp  
deque_test.cpp  
laundry.cpp  

They can be compiled by entering _make_ at the command line.  

A sample invocation of remdup would be:  
./remdup input.txt output.txt  

A sample invocation of laundry would be:  
./laundry laundry.in laundry.out  

laundry.cpp relies on a templated Stack class which can be found in stack.h.  
This class inherits privately from a templated Deque class which can be found in deque.h.  
deque_test.cpp, a gtest-based test driver for the templated Deque class, can be run by entering _make_ at the command line.

Please check the comments in the above programs for any clarifications.