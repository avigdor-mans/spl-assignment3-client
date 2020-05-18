CFLAGS:=-c -Wall -Weffc++ -g -std=c++11 -Iinclude
LDFLAGS:=-lboost_system -pthread

all: EchoClient
	g++ -o bin/StompBookClubClient bin/main.o bin/ConnectionHandler.o bin/IOListener.o bin/StompMessagingProtocol.o bin/ServerListener.o bin/ClientData.o bin/StompFrame.o bin/StompEncoderDecoder.o $(LDFLAGS)

EchoClient: bin/ConnectionHandler.o bin/IOListener.o bin/StompMessagingProtocol.o bin/ServerListener.o bin/ClientData.o bin/StompFrame.o bin/StompEncoderDecoder.o bin/main.o
	
bin/ConnectionHandler.o: src/ConnectionHandler.cpp
	g++ $(CFLAGS) -o bin/ConnectionHandler.o src/ConnectionHandler.cpp

bin/IOListener.o: src/IOListener.cpp
	g++ $(CFLAGS) -o bin/IOListener.o src/IOListener.cpp

bin/StompMessagingProtocol.o: src/StompMessagingProtocol.cpp
	g++ $(CFLAGS) -o bin/StompMessagingProtocol.o src/StompMessagingProtocol.cpp

bin/ServerListener.o: src/ServerListener.cpp
	g++ $(CFLAGS) -o bin/ServerListener.o src/ServerListener.cpp

bin/ClientData.o: src/ClientData.cpp
	g++ $(CFLAGS) -o bin/ClientData.o src/ClientData.cpp

bin/StompFrame.o: src/StompFrame.cpp
	g++ $(CFLAGS) -o bin/StompFrame.o src/StompFrame.cpp

bin/main.o: src/main.cpp
	g++ $(CFLAGS) -o bin/main.o src/main.cpp

bin/StompEncoderDecoder.o: src/StompEncoderDecoder.cpp
	g++ $(CFLAGS) -o bin/StompEncoderDecoder.o src/StompEncoderDecoder.cpp
	
.PHONY: clean
clean:
	rm -f bin/*
