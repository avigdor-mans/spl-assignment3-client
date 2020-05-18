//
// Created by aviv on 14/01/2020.
//

#ifndef UNTITLED_STOMPMESSAGINGPROTOCOL_H
#define UNTITLED_STOMPMESSAGINGPROTOCOL_H

#include "ClientData.h"
#include "ServerListener.h"

#include <mutex>

class ServerListener;
class StompMessagingProtocol {
private:
    ConnectionHandler& connectionHandler;
    ClientData* clientData;
    ServerListener* serverListener;

public:
    /*StompMessagingProtocol(ConnectionHandler& _connectionHandler, ClientData& _clientData,
                           ServerListener* _serverListener); */
    StompMessagingProtocol(ConnectionHandler& _connectionHandler);
    void process(StompFrame stompFrame);
    void setClientData(ClientData * _clientData);
    void setServerListener(ServerListener* _serverListener);

};



#endif //UNTITLED_STOMPMESSAGINGPROTOCOL_H
