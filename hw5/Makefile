CXX = g++
CC = g++

CXXFLAGS = -g -Wall

all: twitter

twitter: user.o datetime.o tweet.o twiteng.o util.o handler.o cmdhandler.o twitter.cpp
	$(CC) $(CXXFLAGS) user.o datetime.o tweet.o twiteng.o util.o handler.o cmdhandler.o twitter.cpp -o twitter

user.o: user.h hsort.h

datetime.o: datetime.h

tweet.o: tweet.h user.o datetime.o

twiteng.o: twiteng.h user.o tweet.o datetime.o twiteng.cpp

util.o: util.h hsort.h tweet.o util.cpp

handler.o: handler.h twiteng.o handler.cpp

cmdhandler.o: cmdhandler.h util.o handler.o cmdhandler.cpp