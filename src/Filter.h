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
#ifndef MB_FILTER_H
#define MB_FILTER_H

#include "Message.h"
#include "Device.h"
#include <stdint.h>

/**
 * @brief Mildabus Filter object
 * 
 */
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
        this->type = t;
        this->value = v;
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