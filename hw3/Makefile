CXX = g++
CC = g++

CXXFLAGS = -g -Wall


all: twitter

twitter: user.o datetime.o tweet.o twiteng.o util.o handler.o cmdhandler.o twitter.cpp

test: user.o datetime.o tweet.o twiteng.o test.cpp

user.o: user.h

datetime.o: datetime.h

tweet.o: tweet.h user.o datetime.o

twiteng.o: twiteng.h user.o tweet.o datetime.o twiteng.cpp

util.o: util.h tweet.o util.cpp

handler.o: handler.h twiteng.o handler.cpp

cmdhandler.o: cmdhandler.h util.o handler.o cmdhandler.cpp