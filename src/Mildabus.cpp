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

/**
 * @brief Construct a new mildabus::mildabus object
 * 
 * @param can mbed CAN bus interface used to initialize MildaBus
 * @param master Defines this device as the MildBus Master node (adress field will be overruled)
 * @param adress override with own adress [0x0000 default]
 */
Mildabus::Mildabus(CAN& can, bool master, uint16_t adress)
{
    if(!can.frequency(500000)){
        Mildabus::raise_exeption(MB_CLOCK_ERROR);
        return;
    }
    
    if(!can.mode(CAN::Normal)){
        Mildabus::raise_exeption(MB_BUS_ERROR);
        return;
    }
    
    Mildabus::master_mode = master;
    
    if(!adress){
        adress = MASTER_ADDRESS;
    }

    Mildabus::set_adress(adress);
    
    can.reset();
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
}

/**
 * @brief Set the Mildabus adress manually.
 * 
 * @param adress for the module
 * @return true success
 * @return false error
 */
bool Mildabus::set_adress(uint16_t adress){
    if(!adress) return false;
    if(Mildabus::master_mode && adress != MASTER_ADDRESS) {
        Mildabus::raise_exception(MB_CONFIG_ERROR);
        return false;
    }

    Mildabus::adress = adress;
    return true;
}

/**
 * @brief 
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