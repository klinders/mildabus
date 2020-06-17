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
#ifndef MB_SUBSCRIPTION_H
#define MB_SUBSCRIPTION_H

#include <mbed.h>
#include "Message.h"
#include "Filter.h"
#include <stdint.h>

class MB_Subscription{
public:
    // Subscription Type
    enum MB_Message::Type type;

    // Specific Error Type filter
    MB_Error::Type error_filter;

    // Specific Event Type filter
    MB_Event::Type event_filter;

    // Specific ID filter
    uint32_t id_filter;

    MB_Filter filter;

private:
    // The Callback object
    Callback<void(MB_Message&)> _callback;

public:
    /**
     * @brief Construct a new Subscription object
     * 
     * @param t     Type
     * @param er    [Error Type]
     * @param ev    [Event Type]
     * @param d     [Device Type]
     * @param id    [Specific ID]
     */
    MB_Subscription(
        MB_Message::Type t, 
        MB_Error::Type er = MB_Error::NONE, 
        MB_Event::Type ev = MB_Event::NONE,
        uint32_t id = 0);
    
    /**
     * @brief Call the handler (If message matches the filters)
     * 
     * @param m     Message
     */
    void call(MB_Message& m);

    /**
     * @brief attach a callback
     * 
     * @param c callback
     */
    void attach(Callback<void(MB_Message&)> c);

    // Operators for the linked list
    friend bool operator==(const MB_Subscription&, const MB_Subscription&);
    friend bool operator!=(const MB_Subscription&, const MB_Subscription&);
};
#endif