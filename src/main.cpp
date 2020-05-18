#include <iostream>
#include <thread>
#include "../include/ConnectionHandler.h"


#include <mutex>
#include "../include/IOListener.h"
#include "../include/ServerListener.h"
int main(int argc, char *argv[]) {




    std::mutex mutexListener;

    bool login = false;
    while (!login) {
        ClientData* clientData = new ClientData();
        string commandFirst;
        cin>>commandFirst;
        if (commandFirst.compare("login")==0) {
            cin>>commandFirst;
            string host = commandFirst.substr(0,commandFirst.find(":"));
            string port = commandFirst.substr(commandFirst.find(':')+1);
            ConnectionHandler connectionHandler(host, stoi(port));
            if (connectionHandler.connect()) {
                    login=true;
                    clientData->connect();
                    StompEncoderDecoder *stopmEncoderDecoder = new StompEncoderDecoder();
                    IOListener ioListener (connectionHandler, clientData, *stopmEncoderDecoder,
                            mutexListener);
                    ServerListener serverListener(clientData, *stopmEncoderDecoder, connectionHandler,
                                                  mutexListener);

                    std::thread th1(std::ref(ioListener));
                    std::thread th2(std::ref(serverListener));
                    th1.join();
                    th2.join();
                    delete stopmEncoderDecoder;
                    }
                }

        else {
            cout << "NOT A LOGIN COMMAND" << endl;
            //getline(cin, commandFirst);
        }
        delete clientData;


    }


    /* login 127.0.0.1:3000 user2 password2 */

    return 0;

}