#ifndef MB_FILTER_H
#define MB_FILTER_H

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
    MB_Filter(Type t = FILTER_NONE, uint8_t v = 0){
        type = t;
        value = v;
    };

    bool filterMessage(MB_Message m);
    uint8_t getValue(void) const{return value;};
    Type getType(void) const{return type;};

    friend bool operator==(const MB_Filter &o1, const MB_Filter &o2){
        bool t = o1.type == o2.type;
        bool v = o1.value == o2.value;
        return (t & v);
    }

    friend bool operator!=(const MB_Filter &o1, const MB_Filter &o2){
        bool t = o1.type == o2.type;
        bool v = o1.value == o2.value;
        return !(t & v);
    }
};
#endif