#include "Error.h"
#include "mbed.h"

typedef enum message_type {
    MB_ABORT_OPERATION,
    MB_HW_RESET,
    MB_SW_RESET,
    MB_CRITICAL_DATA,
    MB_CHANGE_ADDRESS,      /* Assign a new device address (master only) */
    MB_REQUEST_ADDRESS,     /* Request a new device address */

    MB_ACK,                 /* Acknowledge a change */
    MB_PING_ADDRESS,

    MB_REQUEST_DEVICE_ID,   /* Request hardware device ID */
    MB_DEVICE_ID,           /* Module hardware device ID */

    MB_ERROR,
    MB_NONE
} MB_Message_type;

class MB_Message
{
private:
    CANMessage m;
public:
    MB_Message_type type;
    MB_Error error;
    uint8_t from;
    uint8_t to;
    bool incomming;
    uint8_t data[];
    MB_Message(MB_Message_type type = MB_NONE, uint8_t to = 0x00, uint8_t *data = 0);
    bool parseCAN(CANMessage &message);
};
