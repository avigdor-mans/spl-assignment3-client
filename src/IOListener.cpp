//
// Created by aviv on 11/01/2020.
//

#include "../include/IOListener.h"
IOListener::IOListener(ConnectionHandler& _connectionHandler, ClientData* _clientData, StompEncoderDecoder& _stopmEncoderDecoder,
        std::mutex& mutex1)
 : subIdCounter(1), reciptCounter(1), clientData(_clientData), stopmEncoderDecoder(_stopmEncoderDecoder),
  connectionHandler(_connectionHandler), shouldTerminate(false),k(mutex1){

}

void IOListener::operator()() {



    string commandFirst;
    getline(cin, commandFirst);
    commandFirst = "login host" + commandFirst;
    StompFrame *firstFrame = parseInput(commandFirst);
    if (firstFrame != nullptr) {
        k.lock();
        connectionHandler.sendFrameAscii(stopmEncoderDecoder.encode(*firstFrame), '\0');
        k.lock();
        k.unlock();
        bool shouldEnd = false;

        while (clientData->isConnected() && !shouldEnd) {

            string command;
            getline(cin, command);
            StompFrame *frame = parseInput(command);
            if (frame != nullptr ) {

                connectionHandler.sendFrameAscii(stopmEncoderDecoder.encode(*frame), '\0');

            }
            if (command.compare("logout") == 0|| command.find("login")!=std::string::npos)
                shouldEnd = true;

            delete frame;
            frame = nullptr;
        }
        //}
    }
    delete firstFrame;
    firstFrame = nullptr;
}
StompFrame* IOListener::parseInput(string line) {
    StompFrame *stompFrame= new StompFrame();

    if (line.find("login")!=std::string::npos) {
        stompFrame->setCommand("CONNECT");
        cout<<stompFrame->getCommand()<<endl;
        line = line.substr(line.find(" ")+1);
        line = line.substr(line.find(" ")+1);
        string name = line.substr(0,line.find(" "));
        clientData->setUserName(name);
        string passcode = line.substr(line.find(" ")+1);
        stompFrame->addHeader("accept-version:1.2");
        stompFrame->addHeader("login:"+name);
        stompFrame->addHeader("passcode:"+passcode);
        stompFrame->setBody("");



    }
   if (line.find("join")!=std::string::npos)
   {
        stompFrame->setCommand("SUBSCRIBE");
        string destination = line.substr(line.find(' ')+1);
        stompFrame->addHeader("destination:" + destination);
        stompFrame->addHeader("id:" + to_string(subIdCounter));
        stompFrame->addHeader("receipt:" +  to_string(reciptCounter));
        stompFrame->setBody("");
        clientData->addDisplayForReceipt(reciptCounter,"Joined club " +destination );
        reciptCounter++;
        subIdCounter++;
   }
    if (line.find("exit")!=std::string::npos)
    {
        stompFrame->setCommand("UNSUBSCRIBE");
        string destination = line.substr(line.find(' ')+1);
        stompFrame->addHeader("destination:" + destination);
        stompFrame->addHeader("id:" + to_string(subIdCounter));
        stompFrame->addHeader("receipt:" +  to_string(reciptCounter));
        stompFrame->setBody("");
        clientData->addDisplayForReceipt(reciptCounter,"Exit club " +destination );

        reciptCounter++;
        subIdCounter++;
    }

    if (line.find("add")!=std::string::npos)
    {
        stompFrame->setCommand("SEND");
        line = line.substr(line.find(' ') + 1);
        string destination = line.substr(0, line.find(' '));
        stompFrame->addHeader("destination:"+destination);
        string book = line.substr(line.find(' ') + 1);
        stompFrame->setBody(clientData->getName()+" has added the book " + book);
        reciptCounter++;
        subIdCounter++;
        clientData->addBook(destination,book);
    }

    if (line.find("borrow")!=string::npos) {
        stompFrame->setCommand("SEND");
        line = line.substr(line.find(' ') + 1);
        string destination = line.substr(0, line.find(' '));
        stompFrame->addHeader("destination:"+destination);
        string book = line.substr(line.find(' ') + 1);
        stompFrame->setBody(clientData->getName()+" wish to borrow "+book);
        clientData->addBookToWishList(book);
    }

    if (line.find("return")!=string::npos) {
        stompFrame->setCommand("SEND");
        line = line.substr(line.find(' ') + 1);
        string destination = line.substr(0, line.find(' '));
        stompFrame->addHeader("destination:" + destination);
        string book = line.substr(line.find(' ') + 1);
        string owner = clientData->getOwnewr(book);
        if (owner != "" && clientData->isBookExists(destination,book)) {
            stompFrame->setBody("Returning " + book + " to " + owner);
            clientData->returnBorrowedBook(owner,destination,book);
        }
        else {

            delete stompFrame;
            stompFrame = nullptr;
        }
    }

    if (line.find("status")!=string::npos) {
        stompFrame->setCommand("SEND");
        string destination = line.substr(line.find(' ')+1);
        stompFrame->addHeader("destination:"+destination);
        stompFrame->setBody("book status");
    }

    if (line.find("logout")!=string::npos){
        stompFrame->setCommand("DISCONNECT");

        stompFrame->addHeader("receipt:"+to_string(reciptCounter));
        stompFrame->setBody("");
        clientData->addDisplayForReceipt(reciptCounter,"disconnected");
        reciptCounter++;

    }
    return stompFrame;
}
