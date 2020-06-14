#include "Filter.h"
#include "Subscription.h"
#include <stdint.h>

MB_Subscription::MB_Subscription(
    Type t, 
    MB_Error::Type er, 
    MB_Event::Type ev, 
    MB_Device::Type d, 
    uint8_t id)
{
    type = t;
    error_filter = er;
    event_filter = ev;
    device_filter = d;
    id_filter = id;
}

void MB_Subscription::call(MB_Message msg){
    
}

bool operator==(const MB_Subscription &o1,const MB_Subscription &o2){
    bool t = o1.type == o2.type;
    bool c = o1.cb == o2.cb;
    return (t & c);
}

bool operator!=(const MB_Subscription &o1,const MB_Subscription &o2){
    bool t = o1.type == o2.type;
    bool c = o1.cb == o2.cb;
    return !(t & c);
}