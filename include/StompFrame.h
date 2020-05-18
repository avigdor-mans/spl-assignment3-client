#ifndef UNTITLED_STOMPFRAME_H
#define UNTITLED_STOMPFRAME_H

using namespace std;
#include <string>
#include <vector>

class StompFrame {
private:
    string command;
    vector<string> headers;
    string body;

public:
    StompFrame();
    ~StompFrame();
    string getCommand();
    vector<string>& getHeaders();
    string getBody();
    void setCommand(string command);
    void setHeaders(vector<string> headers);
    void addHeader(string header);
    void setBody(string body);
    string toString();
};


#endif //UNTITLED_STOMPFRAME_H