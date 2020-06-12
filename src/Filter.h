#ifndef FILTER_H
#define FILTER_H

#include "Message.h"
#include "Devices.h"



class MB_Filter{
public:
    enum Type{
        FILTER_NONE,
        FILTER_DEVICE,
        FILTER_DATA,
        FILTER_EVENT,
        FILTER_BLOCK
    } type;
    uint8_t value;

public:
    MB_Filter(Type t = FILTER_NONE, uint8_t v = 0);

    bool filterMessage(MB_Message m);
    uint8_t getValue(void) const{return value;};
    Type getType(void) const{return type;};
};
#endif