#include "../include/StompEncoderDecoder.h"
#include <iostream>
using  namespace std;
StompFrame StompEncoderDecoder::decode(string& message) {
    StompFrame stompFrame;

    string command = message.substr(0,message.find('\n'));
    stompFrame.setCommand(command);

    string header ="";
    message = message.substr(message.find('\n')+1);
    while (message.find('\n')!=0){
        header = message.substr(0,message.find('\n'));

        stompFrame.addHeader(header);
        message = message.substr(message.find('\n')+1);
    }
    message = message.substr(message.find('\n')+1);
    string body = message.substr(0,message.find('\n'));
    stompFrame.setBody(body);
    return stompFrame;
}

string StompEncoderDecoder::encode(StompFrame &frame) {
    string strOfFrame = "";
    strOfFrame += frame.getCommand() + "\n";
    for (string header : frame.getHeaders()) {
        strOfFrame += header + "\n";
    }
    strOfFrame += "\n";
    strOfFrame += frame.getBody() + "\n";
    strOfFrame += '\u0000';

  return strOfFrame;
}



