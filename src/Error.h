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
#ifndef MB_EXCEPTIONS_H
#define MB_EXCEPTIONS_H

#include <stdint.h>

/**
 * @struct MB Error Object
 * 
 */
struct MB_Error{
    // Error type
    enum Type{
        NONE = 0x00,
        BUS_ERROR = 0x01,                    /* MB_BUS_ERROR */
        CLOCK_ERROR = 0x02,                  /* MB_CLOCK_ERROR */
        TRANSMIT_ERROR = 0x03,               /* MB_TRANSMIT_ERROR */
        RECEIVE_ERROR = 0x04,                /* MB_BUS_ERROR */
        ADDRESS_COLLISION_ERROR = 0x05,      /* MB_ADDRESS_COLLISION_ERROR */
        CONFIG_ERROR = 0x06                  /* MB_CONFIG_ERROR */
    } type;
    uint32_t time;              /* Current time */
    bool transmitted;           /* Error has been transmitted on the bus */

    MB_Error(){};
    MB_Error(MB_Error::Type t):type(t){};
    ~MB_Error(){};
};

#endif