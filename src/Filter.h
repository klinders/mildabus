#ifndef MB_FILTER_H
#define MB_FILTER_H

#include "Message.h"

struct MB_Filter{
    uint32_t id = 0;
    uint32_t mask = 0;
    uint32_t handle = 0;
    CANFormat format = CANStandard;

    bool active = false;
    MB_Filter(){
    }

    MB_Filter(MB_Message::Type t, uint32_t d = 0, bool extended = true){
        if(!extended){
            MB_Filter(t, (uint8_t)d, extended);
            return;
        }
        if(t != MB_Message::ALL){
            mask = (0xF << 25);
        }else{
            mask = 0;
        }
        // Only messages using extended ID
        id = (t << 25);
        format = CANExtended;

        if(d){
            id |= (DEVICE_ID_MASK & d);
            mask |= DEVICE_ID_MASK;
        }
    }

    MB_Filter(MB_Message::Type t, uint8_t i = 0, bool extended = false){
        // If extended call other constructor
        if(extended) {
            MB_Filter(t, (uint32_t) i);
            return;
        }

        if(t != MB_Message::ALL){
            mask = (0xf << 7);
        }else{
            mask = 0;
        }
        // Normal IDs
        id = (t << 7);
        format = CANStandard;

        if(i){
            id |= (NODE_ID_MASK & i);
            mask |= NODE_ID_MASK;
        }
    }
};

#endif