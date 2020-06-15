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