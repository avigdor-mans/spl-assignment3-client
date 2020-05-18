//
// Created by aviv on 12/01/2020.
//

#ifndef UNTITLED_SERVERLISTENER_H
#define UNTITLED_SERVERLISTENER_H

#include <vector>
#include <unordered_map>
#include <string>
#include "ConnectionHandler.h"
#include "StompEncoderDecoder.h"
#include "StompMessagingProtocol.h"
#include "ClientData.h"
#include <queue>
#include "mutex"

using namespace std;

class ServerListener {
public:
    ServerListener (ClientData* _clientData, StompEncoderDecoder& stompEncoderDecoder, ConnectionHandler& _connectionHandler,
                          mutex& mutex1);
    ServerListener(const ServerListener&);
    ServerListener& operator =(const ServerListener&);
    ~ServerListener();
    void operator()();
    //void Run();
    void addFrameToSend(StompFrame frame);
    mutex& getMutex();
private:
    ClientData* clientData;
    StompEncoderDecoder& stompEncoderDecoder;
    ConnectionHandler& connectionHandler;
    queue<StompFrame> sendQueue;
    mutex &k;


};


#endif //UNTITLED_SERVERLISTENER_H
