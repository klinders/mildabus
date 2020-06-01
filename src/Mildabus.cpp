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
#include "exceptions.h"
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
Mildabus::Mildabus(CAN* can_o, bool master, uint16_t address):can(*can_o)
{
    if(!Mildabus::can.frequency(500000)){
        Mildabus::raise_exception(MB_CLOCK_ERROR);
        return;
    }
    
    if(!Mildabus::can.mode(CAN::Normal)){
        Mildabus::raise_exception(MB_BUS_ERROR);
        return;
    }

    Mildabus::device_id = ((uid[0]^uid[1])^uid[2])&0x0FFFFFFF; // Xor to randomize and truncate 4 bits

    if(master)
        Mildabus::set_address(MASTER_ADDRESS);
    else if(address)
        Mildabus::set_address(address);
    
    Mildabus::master_mode = master;

}

/**
 * @brief Prepare the mildabus for operation
 * 
 * @return true success
 * @return false error
 */
bool Mildabus::prepare(void){
    // We need to:
    //// Check for module ID
    //// Request module ID if applicable
    //// 
    
    Mildabus::can.reset();

    if(!Mildabus::address)
        Mildabus::request_address(true); // Request and block

    Mildabus::can.attach(Callback<void(void)>(Mildabus::can_rx_handler), CAN::RxIrq); // Received
    Mildabus::can.attach(Callback<void(void)>(Mildabus::can_tx_handler), CAN::TxIrq); // Transmitted or aborted
    Mildabus::can.attach(Callback<void(void)>(Mildabus::can_wu_handler), CAN::WuIrq); // Wake Up

    return true;
}

/**
 * @brief Set the Mildabus address manually.
 * 
 * @param address for the module
 * @return true success
 * @return false error
 */
bool Mildabus::set_address(uint16_t address){
    if(!address) return false;
    if(Mildabus::master_mode && address != MASTER_ADDRESS) {
        Mildabus::raise_exception(MB_CONFIG_ERROR);
        return false;
    }

    Mildabus::address = address;
    return true;
}

uint16_t Mildabus::request_address(bool blocking){
    const char data[] = {0x22, 0x22};
    CANMessage tx_msg(Mildabus::device_id, data, 1, CANData, CANExtended);
    Mildabus::can.write(tx_msg);

    CANMessage rx_msg;
    // Block until the 
    while(1){
        if(Mildabus::can.read(rx_msg, 0)){
            if(rx_msg.id == Mildabus::device_id && rx_msg.data[0] == ASSIGN_ADDRESS){
                Mildabus::address = rx_msg.data[1];
                uint8_t cnf_data[] = {ADDRESS_CONFIRM};
                Mildabus::transmit(DESTINATION_ALL, cnf_data, 1);
                break;
            }
        }
    }
    return Mildabus::address;
}

/**
 * @private Raise an mildabus exception. Will be transmitted if the bus is active.
 * 
 * @param e @ref MB_Error_Type 
 */
void Mildabus::raise_exception(MB_Error_Type e){
    MB_Error err;
    err.type = e;
    // TO DO: Setup systick/rtc
    err.time = 0;
    Mildabus::error[Mildabus::error_count] = err;
    // Transmit the fault if the bus is active
    if(Mildabus::active){
        Mildabus::transmit_exceptions();
    }

    // Raise the counter
    if(Mildabus::error_count < 7) {
        Mildabus::error_count++;
    }else{
        // Roll over
        Mildabus::error_count = 0;
    }
}

bool Mildabus::transmit_exceptions(void){
    // Nothing yet
}

void Mildabus::can_rx_handler(void){

}

void Mildabus::can_tx_handler(void){

}

void Mildabus::can_wu_handler(void){

}