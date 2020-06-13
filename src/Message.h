#ifndef MB_MESSAGE_H
#define MB_MESSAGE_H

#include "Error.h"
#include "mbed.h"

/*  Define all important adresses */
#define MASTER_ADDRESS 0x22
#define DESTINATION_ALL 0x00


/**
 * @brief Mildabus Message Class
 * 
 * @param error     MB_Error class (if aplicable)
 * @param to        Address to where the message was/will be sent
 *                  If the message is incomming this will be the device address.
 * @param from      Address from where the message was/will be sent
 * @param incomming True if the message is received.
 */
class MB_Message:public CANMessage
{
public:
    enum Function_Code {
        NMT = 0x0,
        GFC = 0x1, // Not used!
        SYNC = 0x2,
        EMCY = 0x3,
        TSTMP = 0x4,         
        EVENT_TX = 0x5,      /* Event (broadcast) */ 
        EVENT_RX = 0x6,      
        DATA_TX = 0x7,       /* Data response */
        DATA_RX = 0x8,       /* Data Request */
        BLOCK_TX = 0x9,      /* Data Block Response */
        BLOCK_RX = 0xA,      /* Data Block Request */ 
        SYS_TX = 0xB,        /* System parameter Response */
        SYS_RX = 0xC,        /* System Parameter Request */
        HRTBT = 0xD,         /* Heartbeat */
        DCNF_TX = 0xE,       /* Assign a new device address (master only) */
        DCNF_RX = 0xF        /* Request a new device address */
    } fcode;
private:
    MB_Error error;
    uint8_t to;
    uint8_t from;
    bool incomming;
public:
    /** Creates empty CAN message.
     */
    MB_Message() : CANMessage()
    {
        type   = CANData;
        format = CANStandard;
    }
    MB_Error getError(void) const{return error;};
    uint8_t getTo(void) const{return to;};
    uint8_t getFrom(void) const{return from;};
    bool isIncomming(void) const{return incomming;};
};
#endif