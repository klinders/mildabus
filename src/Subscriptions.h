#include <mbed.h>
#include "Filter.h"

class MB_Subscription{
public:
    enum Type {
        MB_EVENT,
        MB_DATA,
        MB_ERROR,
        MB_ALL
    } type;
    MB_Filter filter;

public:
    MB_Subscription(Type t = MB_ALL, MB_Filter f = MB_Filter()):filter(f){
        type = t;
    }
};