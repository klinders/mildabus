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
#ifndef MB_MESSAGE_H
#define MB_MESSAGE_H

#include "Error.h"
#include "Event.h"
#include "Device.h"
#include "mbed.h"

/*  Define all important adresses */
#define MASTER_ADDRESS 0x22
#define DESTINATION_ALL 0x00

/* define other things */
#define NODE_ID_MASK    0b00001111111                       // Mask for the node ID
#define DEVICE_ID_MASK  0b00001111111111111111111111111     // Mask for the Device ID
#define FUNCTION_MASK   0b1111                              // Mask for the function code

#define FUNCTION_CODE(ID)   (ID&FUNCTION_MASK)              // Macro to define function code
#define DEVICE_ID(ID)       (ID&DEVICE_ID_MASK)             // Macro to define device id
#define NODE_ID(ID)         (ID&NODE_ID_MASK)               // Macro to define node id



/**
 * @brief Mildabus Message Object (extends mbed::CANMessage)
 * 
 */
class MB_Message : public CANMessage
{
public:
    // Under the hood message codes
    enum Type {
        NMT = 0x0,
        GFC = 0x1,              /* Not used! */
        SYNC = 0x2,             /* Synchronization */
        ERROR = 0x3,             /* Emergency (error) */
        TSTMP = 0x4,            /* Timestamp message */
        EVENT_TX = 0x5,         /* Event (broadcast) */ 
        EVENT_RX = 0x6,         /* Event (request?) */
        DATA_TX = 0x7,          /* Data response */
        DATA_RX = 0x8,          /* Data Request */
        BLOCK_TX = 0x9,         /* Data Block Response */
        BLOCK_RX = 0xA,         /* Data Block Request */ 
        SYS_TX = 0xB,           /* System parameter Response */
        SYS_RX = 0xC,           /* System Parameter Request */
        HRTBT = 0xD,            /* Heartbeat */
        DCNF_TX = 0xE,          /* Assign a new device address (master only) */
        DCNF_RX = 0xF,           /* Request a new device address */
        
        // Types for filter
        ALL,
        NONE,
        // counter
        TYPE_COUNT
    } type;
    // Mildabus Error
    MB_Error error;
    // Mildabus Event
    MB_Event event;
    // Mildabus Device TO
    MB_Device to;
    // Mildabus Device From
    MB_Device from;

public:
    /**
     * @brief Construct a new Message object
     * 
     */
    MB_Message();

    /**
     * @brief parse the message (To fill the MB specific parts)
     * 
     */
    void parse(void);

    /**
     * @brief Get the Error object
     * 
     * @return MB_Error 
     */
    MB_Error getError(void) const{return error;};

    /**
     * @brief Get the Event object
     * 
     * @return MB_Event 
     */
    MB_Event getEvent(void) const{return event;};
};
#endif