#include "../include/StompFrame.h"



string StompFrame::getCommand() {
    return command;
}
void StompFrame::setCommand(string command){
    this->command = command;
}
void StompFrame::addHeader(string header) {
    this->headers.push_back(header);
}
vector<string>& StompFrame::getHeaders() {
    return headers;
}

string StompFrame::getBody() {
    return body;
}

void StompFrame::setBody(string body) {
 this->body=body;
}

StompFrame::StompFrame():command(""),headers(),body("") {

}

StompFrame::~StompFrame() = default;

string StompFrame::toString() {
    string strOfFrame = "";
      strOfFrame += command + "\n";
      for (string header : headers) {
          strOfFrame += header + "\n";
      }
    strOfFrame += "\n";
    strOfFrame += body + "\n";
    return strOfFrame;
}