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