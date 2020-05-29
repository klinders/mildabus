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
#include "mildabus.h"
#include "can.h"
#include <mbed.h>

/**
 * @brief Construct a new mildabus::mildabus object
 * 
 * @param can mbed CAN bus interface used to initialize MildaBus
 * @param master Defines this device as the MildBus Master node (adress field will be overruled)
 * @param adress override with own adress [0x0000 default]
 */
mildabus::mildabus(CAN_TypeDef can, bool master = false, uint32_t adress = 0x0000)
{

}

/**
 * @brief Prepare the mildabus for operation
 * 
 */
void mildabus::prepare(void){
    // We need to:
    //// Setup the CAN Bus
    //// Check for module ID
    //// Request module ID if applicable
    //// 
}
