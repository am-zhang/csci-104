HW5 consists of one main file that can be compiled and run:  
twitter.cpp

For the second part of the Twitter project, we focused on adding support for @-mentions, writing a sorting algorithm used in the microblog engine, and supporting two new commands (FOLLOW and SAVE).  
The FOLLOW name_of_follower name_to_follow command allows the user with the given name to start to FOLLOW another user. The SAVE new_db_filename command allows the user to save a new database file of all the users, their following relationships, and tweets based on any updates performed since reading in the database at startup.  
Support was added for @-mentions, appropriate visibility of tweets starting with @-mentions, and a separate @-mention feed.  
Now when we quit the program, we dump the main feed files (e.g. Mark.feed, Sam.feed, etc.) as well as a users mentions feed to a separate file named: user.mentions (e.g. Mark.mentions, Sam.mentions, etc.).

hsort.h  
This templated function of the Heapsort algorithm works with any class T. It runs in O(n log(n)). The sorting is performed in-place (without the usage of a second array). The hsort() function takes in a vector. The Heapsort algorithm also takes a comparator object (i.e., functor) that has an operator() defined for it to produce different orderings based on the functor.

heap.h  
Heap.h is my own m-ary Heap class. Rather than specifying a specific type of heap (Min- or Max-Heap) we pass in a Comparator object so that if the comparator object functor implements a less-than check then we will have a min-heap. If the Comparator object functor implements a greater-than check we will have a max-heap. 

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
