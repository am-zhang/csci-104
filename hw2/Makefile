all: setops_test majors

majors: majors.cpp setops.o
	g++ -g -Wall -std=c++11 setops.o majors.cpp -o majors

setops_test: setops_test.cpp setops.o
	g++ -g -Wall -std=c++11 setops.o setops_test.cpp -o setops_test

setops.o: setops.h setops.cpp
	g++ -g -Wall -c setops.cpp -o setops.o

clean:
	rm setops_test;
	rm setops.o;
	rm majors;