//
// Created by aviv on 11/01/2020.
//

#ifndef UNTITLED_IOLISTENER_H
#define UNTITLED_IOLISTENER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ConnectionHandler.h"
#include "StompFrame.h"
#include "ClientData.h"
#include "StompEncoderDecoder.h"
#include <mutex>

using namespace std;

class IOListener {
public:

    IOListener(ConnectionHandler& connectionHandler, ClientData* clientData, StompEncoderDecoder& stopmEncoderDecoder
    ,mutex&);
    void operator()();


private:
    StompFrame* parseInput(string line);
    int subIdCounter;
    int reciptCounter;
    ClientData* clientData;
    StompEncoderDecoder& stopmEncoderDecoder;
    ConnectionHandler &connectionHandler;
    bool shouldTerminate;
    std::mutex &k;
};


#endif //UNTITLED_IOLISTENER_H
