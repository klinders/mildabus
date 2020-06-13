#ifndef MB_SUBSCRIPTIONS_H
#define MB_SUBSCRIPTIONS_H

#include <mbed.h>
#include "Filter.h"

class MB_Subscription{
public:
    enum Type {
        MB_EVENT,
        MB_DATA,
        MB_ERROR,
        MB_NMT,
        MB_DCNF,
        MB_BLOCK,
        MB_ALL
    } type;
    MB_Filter filter;
    Callback<void(MB_Message)> cb;

public:
    MB_Subscription(Type t = MB_ALL, MB_Filter f = MB_Filter()):filter(f){
        type = t;
    }
    friend bool operator==(const MB_Subscription &o1,const MB_Subscription &o2){
        bool t = o1.type == o2.type;
        bool f = o1.filter == o2.filter;
        bool c = o1.cb == o2.cb;
        return (t & f & c);
    }
    friend bool operator!=(const MB_Subscription &o1,const MB_Subscription &o2){
        bool t = o1.type == o2.type;
        bool f = o1.filter == o2.filter;
        bool c = o1.cb == o2.cb;
        return !(t & f & c);
    }
};
#endif