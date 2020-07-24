HW1 consists of three main files that can be compiled and run:  
sum_pairs.cpp  
tweet_parse.cpp  
str_test.cpp  with str.cpp

sum_pairs.cpp  
This program reads in a text file with a single integer on each line and then outputs the sum of the first integer and last integer, second, and second to last integer, etc. If there is an odd number of integers, it adds the middle one to itself. The program must get the name of the text file as the first command line argument. The name of the output must be given as the next command line argument.

tweet_parse.cpp  
This program reads a text file that mimics a 'tweet'. All words of a single tweet are on one line of text with users preceded by an '@' and keywords marked by '#'. This program reads a file whose name is specified at the command line and outputs the following:
1. The number of tweets (number of lines in the file not counting empty lines)  
2. All the unique users mentioned in the tweets in the file  
3. All the unique hashtags mentioned in the file  

str.h and str.cpp  
This program implements my own version of the std::string class. A major portion of this problem is to add appropriate operator overload, assignment operators, copy constructors, and a destructor. 

Compile sum_pairs.cpp with the following command:  
g++ -g -Wall -std=c++11 sum_pairs.cpp -o sum_pairs  
A sample invocation of the program would be:  
./sum_pairs input.txt output.txt

Compile tweet_parse.cpp with the following command:  
g++ -g -Wall -std=c++11 tweet_parse.cpp -o tweet_parse  
A sample invocation of the program would be:  
./tweet_parse tweets.txt

Compile str_test.cpp with the following command:  
g++ -g -Wall -std=c++11 str.cpp str_test.cpp -o str_test  
A sample invocation of the program would be:  
./str_test

Please check the comments in the above programs for any clarifications.
