//
// Created by aviv on 12/01/2020.
//

#include "../include/StompMessagingProtocol.h"
#include "../include/ServerListener.h"

ServerListener::ServerListener(ClientData *_clientData, StompEncoderDecoder &_stompEncoderDecoder,
                                     ConnectionHandler &_connectionHandler, std::mutex& mutex1) : clientData(_clientData),stompEncoderDecoder(_stompEncoderDecoder),
                               connectionHandler(_connectionHandler),sendQueue(), k(mutex1)
{

}
ServerListener::~ServerListener() {
    while (!sendQueue.empty())
    {
        sendQueue.pop();
    }
}

ServerListener& ServerListener:: operator=(const ServerListener& serverListener) {
    if (this != &serverListener)
    {
        this->clientData = nullptr;

        while (!sendQueue.empty()){
            sendQueue.pop();

        }

        this->clientData=serverListener.clientData;

    }

    return *this;
}
void ServerListener::operator()() {
   StompMessagingProtocol stompMessagingProtocol(connectionHandler);
   stompMessagingProtocol.setClientData(clientData);
   stompMessagingProtocol.setServerListener(this);


        while (clientData->isConnected()) {
            string msg = "";
            connectionHandler.getFrameAscii(msg, '\0');

            StompFrame stompFrame = stompEncoderDecoder.decode(msg);


            stompMessagingProtocol.process(stompFrame);

            while (!sendQueue.empty()) {
                connectionHandler.sendFrameAscii(stompEncoderDecoder.encode(sendQueue.front()), '\0');
                sendQueue.pop();
            }

    }
}

void ServerListener::addFrameToSend(StompFrame frame) {
    sendQueue.push(frame);

}

ServerListener::ServerListener(const ServerListener &other): clientData(other.clientData),stompEncoderDecoder(other.stompEncoderDecoder),
connectionHandler(other.connectionHandler),sendQueue(other.sendQueue),k(other.k){

}

mutex &ServerListener::getMutex() {
    return k;
}


