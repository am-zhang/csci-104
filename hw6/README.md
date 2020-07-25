HW6 consists of two main files that can be compiled and run:  
sentences.cpp  
sat_solver.cpp

sentences.cpp  
An English-language sentence contains a subject and a verb. The subject may be preceded by adjectives while the verb may be followed by adverbs. Consider the problem of taking a set of options for each part of a sentence and generating the various legal sentences. A legal sentence is of the following form:  
The (adjective) subject verb (adverb).  
This program reads in the word options for each part of speech and then uses a recursive approach to generate and output all the possible sentences to a new text file, as well as indicating how many sentences were generated.  
Each part of speech must be on one line of the file with words separated by spaces. The first line should contain the adjective(s), the second line the subject(s), the third line the verb(s), and the fourth line the adverb(s). The adjective and adverb lines might only contain whitespace and no words.

sat_solver.cpp  
A simple boolean satisfiability solver, which seeks to answer whether there exists an assignment of 0's and 1's to binary variables {x1, x2, ..., xn} that will cause a Boolean expression (AND, OR, NOT) to evaluate to true. The conjunctive normal form (CNF) is used, for example:  
(x1 || x2 || !x4) && (x3) && (!x1 || !x2)  
The expressions must be given as a text file in a DIMACs format.  
This program reads in one of these DIMACS CNF expressions from a file (provided as the 1st argument on the command line), and uses a recursive backtracking search to attempt to find a satisfying assignment of 0's (False) and 1's (True) such that the expression evaluates to true. The program outputs (as a file whose name is specified as the 2nd argument on the command line) an assignment of variable values if a solution is found or No solution if no solution exists.

Both can be compiled by entering _make_ at the command line.  

A sample invocation of sentences would be:  
./sentences words1.in words1.out  

A sample invocation of sat_solver would be:  
./sat_solver test.cnf test.out  

Please check the comments in the above programs for any clarifications.
