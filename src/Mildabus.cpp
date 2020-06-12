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
#include "Mildabus.h"
#include <mbed.h>

// Device Unique ID
uint32_t *uid = (uint32_t *)UID_BASE;
void can_handler(void);

/**
 * @brief Construct a new mildabus::mildabus object
 * 
 * @param can mbed CAN bus interface used to initialize MildaBus
 * @param master Defines this device as the MildBus Master node (address field will be overruled)
 * @param address override with own address [0x0000 default]
 */
Mildabus::Mildabus(CAN* can_o, bool master = false, uint8_t address = 0x00):can(*can_o)
{
    if(!Mildabus::can.frequency(500000)){
        Mildabus::raiseException(MB_Error::CLOCK_ERROR);
        return;
    }
    
    if(!Mildabus::can.mode(CAN::Normal)){
        Mildabus::raiseException(MB_Error::BUS_ERROR);
        return;
    }

    Mildabus::device_id = ((uid[0]^uid[1])^uid[2])&0x00FFFFFF; // Xor to join and truncate 4 bits

    if(master){
        Mildabus::setAddress(MASTER_ADDRESS);
    }else if(address){
        Mildabus::setAddress(address);
    }
    Mildabus::master_mode = master;
}

/**
 * @brief Prepare the mildabus for operation
 * 
 * @return true success
 * @return false error
 */
bool Mildabus::getConnected(void){
    // We need to:
    //// Check for module ID
    //// Request module ID if applicable
    //// 
    
    Mildabus::can.reset();

    if(!Mildabus::address){
        Mildabus::requestAddress(true); // Request and block
    }
    Mildabus::can.attach(callback(this, &Mildabus::can_rx_handler), CAN::RxIrq); // Received
    Mildabus::can.attach(callback(this, &Mildabus::can_tx_handler), CAN::TxIrq); // Transmitted or aborted
    Mildabus::can.attach(callback(this, &Mildabus::can_wu_handler), CAN::WuIrq); // Wake Up

    return true;
}

/**
 * @brief Set the Mildabus address manually.
 * 
 * @param address for the module
 * @return true success
 * @return false error
 */
bool Mildabus::setAddress(uint16_t address){
    if(!address) return false;
    if(Mildabus::master_mode && address != MASTER_ADDRESS) {
        Mildabus::raiseException(MB_Error::CONFIG_ERROR);
        return false;
    }

    Mildabus::address = address;
    return true;
}

void Mildabus::requestAddress(bool blocking){
    MB_Message msg;
    

    // Reset the MB address if one is there.    
    Mildabus::address = 0;

    Mildabus::send(msg);
    // Block until the address is filled
    if(blocking) while(!Mildabus::address);
}

/**
 * @private Raise an mildabus exception. Will be transmitted if the bus is active.
 * 
 * @param e @ref MB_Error_Type 
 */
void Mildabus::raiseException(MB_Error::Type e){
    MB_Error err;
    err.type = e;
    // TO DO: Setup systick/rtc
    err.time = 0;
    Mildabus::error[Mildabus::error_count] = err;
    // Transmit the fault if the bus is active
    if(Mildabus::active){
        Mildabus::transmitExceptions();
    }

    //Mildabus::can.filter();

    // Raise the counter
    if(Mildabus::error_count < 7) {
        Mildabus::error_count++;
    }else{
        // Roll over
        Mildabus::error_count = 0;
    }
}

bool Mildabus::send(MB_Message msg){

}

bool Mildabus::read(MB_Message &message, MB_Filter filter){
    int handle = 0;

    if(filter.type != MB_Filter::FILTER_NONE){
        // TBD
    }

    MB_Message msg;

    if(!Mildabus::can.read(msg, handle)) return false;
    
    return true;
}

bool Mildabus::transmitExceptions(void){
    // Nothing yet
    return true;
}

void Mildabus::can_rx_handler(void){
    MB_Message message;
    if(Mildabus::read(message)){

    }
}

void Mildabus::can_tx_handler(void){

}

void Mildabus::can_wu_handler(void){

}