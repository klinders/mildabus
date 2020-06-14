#include "Message.h"
#include <stdint.h>

MB_Message::MB_Message(){
    MB_Message::type = MB_Message::DATA_TX;
}

void MB_Message::parse(){
    if(this->len){
        // Get the first 4 bits for the function code
        this->type = (MB_Message::Type)(FUNCTION_CODE(this->id));
        
        if(this->format == CANFormat::CANExtended){
            // Get the last 25 bits for the full device ID
            this->from.device_id = DEVICE_ID(this->id); 
        }else{
            // Get the last 25 bits for the node ID
            this->from.id = (uint8_t)(NODE_ID(this->id));
        }
    }
}