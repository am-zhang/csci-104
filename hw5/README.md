HW5 consists of one main file that can be compiled and run:  
twitter.cpp

This can be compiled by entering _make_ at the command line.  

A sample invocation of twitter would be:  
./twitter twitter.dat  

This also program relies on changes made to:  
user.cpp  
datetime.cpp   
twiteng.cpp  
cmdhandler.cpp  
util.cpp  

twitter.cpp relies on a templated function implementation of a heapsort algorithm which can be found in hsort.h.  

heap.h contains an m-ary Heap class which takes in a Comparator object in order to implement a min or max heap.

Please check the comments in the above programs for any clarifications.