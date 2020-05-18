//
// Created by aviv on 14/01/2020.
//

#include "../include/StompMessagingProtocol.h"
//StompMessagingProtocol::StompMessagingProtocol(ConnectionHandler& _connectionHandler, ClientData& _clientData,
//                                                 ServerListener* _serverListener) : connectionHandler(_connectionHandler),
//                                                                                    clientData(_clientData),serverListener(_serverListener){
//
//}
StompMessagingProtocol::StompMessagingProtocol(ConnectionHandler &_connectionHandler) : connectionHandler(_connectionHandler),
clientData(nullptr),serverListener(nullptr){

}
void StompMessagingProtocol::process(StompFrame stompFrame) {
    bool hasAddedBook = false;
    if (stompFrame.getCommand().compare("CONNECTED") == 0) {

        cout << "Login successful" << endl;
        serverListener->getMutex().unlock();

    }
    if (stompFrame.getCommand().compare("RECEIPT") == 0) {
        //lock
        int receiptId = stoi(stompFrame.getHeaders()[0].substr(stompFrame.getHeaders()[0].find(':')+1));

        //   if (line.find("login")!=std::string::npos) {
        if (clientData->getDisplayByReceipt(receiptId).find("Joined") != std::string::npos) {
            cout <<"in protocol:" + clientData->getDisplayByReceipt(receiptId) << endl;
        }
        if (clientData->getDisplayByReceipt(receiptId).find("Exited") != std::string::npos) {
            cout <<"in protocol:" + clientData->getDisplayByReceipt(receiptId) << endl;
        }
        if (clientData->getDisplayByReceipt(receiptId).find("disconnected") != std::string::npos) {
            clientData->DisConnect();

        }
    }
    if (stompFrame.getCommand().compare("ERROR") == 0) {

        cout<<stompFrame.getBody()<<endl;

        connectionHandler.close();
        clientData->DisConnect();
        serverListener->getMutex().unlock();

    }
    if (stompFrame.getCommand().compare("MESSAGE") == 0) {
        string body = stompFrame.getBody();
        string topic;
        for (string header : stompFrame.getHeaders()) {
            if (header.find("destination") != std::string::npos) {
                topic = header.substr(header.find(':') + 1);
            }
        }
        if (body.find("Taking") != string::npos) {
            string book = body.substr(body.find(' ')+1);
            book = book.substr(0, book.find("from")-1);
            if (body.find(clientData->getName()) != string::npos) {
                clientData->removeBook(topic, book);
            }
        }
        if (body.find("has added the book") != string::npos) {

            hasAddedBook = true;
        }

        if (body.find("has") != string::npos && !hasAddedBook) {
            string book = body.substr(body.find("has") + 4);
            StompFrame takingBookFrame;
            bool meTaking = false;
            for (string b : clientData->getWishList()) {
                if (book.compare(b) == 0 && !meTaking) {
                    string takingFromName = body.substr(0, body.find(' '));
                    takingBookFrame.setCommand("SEND");
                    takingBookFrame.addHeader("destination:" + topic);
                    takingBookFrame.setBody("Taking " + book + " from " + takingFromName);
                    clientData->addBorrowedBook(takingFromName, topic, book);
                    meTaking = true;
                }
            }
            if (meTaking)
            {
                clientData->removeFromWishList(book);
                serverListener->addFrameToSend(takingBookFrame);
            }
        }
        if (body.find("wish to borrow") != string::npos) {
            string book = body.substr(body.find("borrow") + 7);
            if (clientData->isBookExists(topic, book)) {
                //   std::lock_guard<std::mutex> lock(mutex);
                StompFrame iHaveBookFrame;
                iHaveBookFrame.setCommand("SEND");
                iHaveBookFrame.addHeader("destination:" + topic);
                iHaveBookFrame.setBody(clientData->getName() + " has " + book);
                serverListener->addFrameToSend(iHaveBookFrame);
            }
        }
        //

        if (body.find("Returning") != string::npos) {
            string owner = body.substr(body.find("to") + 3);

            string book = body.substr(0, body.find("to"));
            book = book.substr(book.find(' ') + 1);

            if (owner.compare(clientData->getName()) == 0) {
                clientData->addBook(topic, book);
            }
        }

        //
        if (stompFrame.getBody().compare("book status") == 0) {
            vector<string> *books = clientData->getBooksForATopic(topic);

            StompFrame myBooksFrame;
            myBooksFrame.setCommand("SEND");
            myBooksFrame.addHeader("destination:" + topic);
            string returnBody = clientData->getName() + ":";
            bool bookExist = false;
            for (string a: *books) {
                returnBody += a + ",";
                bookExist = true;
            }
            if (bookExist)
                returnBody = returnBody.substr(0, returnBody.size() - 1);
            else
                delete books;
            myBooksFrame.setBody(returnBody);
            serverListener->addFrameToSend(myBooksFrame);
        }
    }
}



void StompMessagingProtocol::setClientData(ClientData *_clientData) {
    this->clientData = _clientData;
}

void StompMessagingProtocol::setServerListener(ServerListener *_serverListener) {
    this->serverListener = _serverListener;
}




