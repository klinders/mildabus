#include "Error.h"
#include "mbed.h"

enum function_code {
    MB_NMT = 0x0,
    MB_GFC = 0x1, // Not used!
    MB_SYNC = 0x2,
    MB_EMCY = 0x3,
    MB_TSTMP = 0x4,         
    MB_EVENT_TX = 0x5,      /* Event (broadcast) */ 
    MB_EVENT_RX = 0x6,      
    MB_DATA_TX = 0x7,       /* Data response */
    MB_DATA_RX = 0x8,       /* Data Request */
    MB_BLOCK_TX = 0x9,      /* Data Block Response */
    MB_BLOCK_RX = 0xA,      /* Data Block Request */ 
    MB_SYS_TX = 0xB,        /* System parameter Response */
    MB_SYS_RX = 0xC,        /* System Parameter Request */
    MB_HRTBT = 0xD,         /* Heartbeat */
    MB_DCNF_TX = 0xE,       /* Assign a new device address (master only) */
    MB_DCNF_RX = 0xF        /* Request a new device address */
};

typedef enum message_type {
    MB_REQUEST_ID,
    MB_TRANSMIT_ID,
    MB_ERROR
} MB_Message_Type;

class MB_Message:public CANMessage
{
private:
    function_code fcode;
public:
    /** Creates empty CAN message.
     */
    MB_Message() : CANMessage()
    {
        type   = CANData;
        format = CANStandard;
    }

    MB_Message_Type m_type;
    MB_Error error;
    uint8_t to;
    uint8_t from;
    bool incomming;
};
