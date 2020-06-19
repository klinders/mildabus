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
#ifndef MB_DEVICES_H
#define MB_DEVICES_H

#include <stdint.h>

/**
 * @brief Mildabus Device Object
 * 
 */
class MB_Device{
public:
    /**
     * @brief Device Type
     * 
     */
    enum Type {
        MASTER = 0x00,
        NAVLIGHT = 0x01,
        LIGHT = 0x02,
        DASHBOARD = 0x03,
        VSENSE = 0x04,
        TSENSE = 0x05,
        PSENSE = 0x06,
        ISENSE = 0x07,
        LSENSE = 0x08,
        DOORSENSE = 0x09,
        LOCK = 0x0A,
        KEYPAD = 0x0B,
        NONE = 0xFF
    } type;

    /**
     * @brief Node ID
     * 
     */
    uint8_t id;

    /**
     * @brief Device ID
     * 
     */
    uint32_t device_id;

    MB_Device(){};
    MB_Device(uint8_t address):id(address){};
};
#endif