#ifndef MB_MESSAGE_H
#define MB_MESSAGE_H

#include "Error.h"
#include "Event.h"
#include "Device.h"
#include "mbed.h"

/*  Define all important adresses */
#define MASTER_ADDRESS 0x22
#define DESTINATION_ALL 0x00

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
        DCNF_RX = 0xF           /* Request a new device address */
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