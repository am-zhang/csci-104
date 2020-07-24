HW2 consists of two main files that can be compiled and run:  
setops_test.cpp  
majors.cpp

setops.h and setops.cpp  
This program creates a separate library that contains the following global level functions (not part of a class) which will perform set operations on std::set<std::string>:  

// Computes the intersection of s1 and s2  
std::set<std::string> operator&(const std::set<std::string>& s1, const std::set<std::string>& s2);

// Computes the union of s1 and s2  
std::set<std::string> operator|(const std::set<std::string>& s1, const std::set<std::string>& s2);

// Computes the difference of s1 - s2  
std::set<std::string> operator-(const std::set<std::string>& s1, const std::set<std::string>& s2);                                 
The runtime of each operation is in O(nlog(n)). No STL library functions are used in the implementations of these programs.

majors.cpp  
This program reads in student names and their major(s) and then allows queries as to which students have declared a certain major, or double, triple, quadruple (any number of) major(s). It stores data in a map to allow for efficient computation of what students have declared a given major to produce the answer to the queries from the command file. For double or triple majors, this program relies on operations declared in setops.h/.cpp.  

Both can be compiled by entering _make_ at the command line.  

A sample invocation of setops_test would be:  
./setops_test  

A sample invocation of majors would be:  
./majors majors1.in majors1.cmd majors1.out  

Please check the comments in the above programs for any clarifications.
