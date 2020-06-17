/*
 * MIT License
 *
 * Copyright (c) 2020 klinders
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "Filter.h"
#include "Subscription.h"
#include "Message.h"
#include <stdint.h>

MB_Subscription::MB_Subscription(MB_Message::Type t, MB_Error::Type er, MB_Event::Type ev, uint32_t id):
    type(t),
    error_filter(er),
    event_filter(ev),
    id_filter(id){}

void MB_Subscription::attach(Callback<void(MB_Message&)> c){
    _callback = c;
}

void MB_Subscription::call(MB_Message& msg){

    // Type specific filters
    switch (type)
    {
    case MB_Message::ERROR:
        if(error_filter != MB_Error::NONE){
            if(error_filter != msg.error.type){
                return;
            }
        }
        break;
    case MB_Message::EVENT_TX:
        if(event_filter != MB_Event::NONE){
            if(event_filter != msg.event.type){
                return;
            }
        }
        break;
    default:
        break;
    }

    // If we have an ID filter installed
    if(id_filter != 0){
        if(id_filter != msg.id){
            return;
        }
    }
    // If we are here, we passed all filters
    _callback(msg);
}

bool operator==(const MB_Subscription &o1,const MB_Subscription &o2){
    bool t = o1.type == o2.type;
    bool c = o1._callback == o2._callback;
    return (t & c);
}

bool operator!=(const MB_Subscription &o1,const MB_Subscription &o2){
    bool t = o1.type == o2.type;
    bool c = o1._callback == o2._callback;
    return !(t & c);
}