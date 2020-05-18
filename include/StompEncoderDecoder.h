#ifndef UNTITLED2_STOMPENCODERDECODER_H
#define UNTITLED2_STOMPENCODERDECODER_H


#include <zconf.h>
#include <string>
#include "StompFrame.h"
using namespace std;

class StompEncoderDecoder {

private:

public:
    StompFrame decode(string& message);
    string encode(StompFrame &frame);
    //void pushByte(Byte nextByte);
    //string popString();
};


#endif //UNTITLED2_STOMPENCODERDECODER_H