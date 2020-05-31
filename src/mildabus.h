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
#ifndef MILDABUS_H
#define MILDABUS_H
#include <mbed.h>

#define MASTER_ADDRESS 0x22
typedef enum MB_Error_Struct{
    MB_BUS_ERROR,
    MB_TRANSMIT_ERROR,
    MB_RECEIVE_ERROR,
    MB_ADRESS_COLLISION_ERROR
} MB_Error_TypeDef;

class mildabus
{
private:
    bool master_mode;
public:
    mildabus(CAN_TypeDef can, bool master = false, uint32_t adress = 0x0000);
    void prepare(void);
    uint32_t register_self(uint32_t adress = 0x99);
    void transmit(uint32_t dest, uint8_t *data, int length);
    uint8_t &receive(int length = 1);
    void raise_exeption(MB_Error_TypeDef e);
};

#endif
