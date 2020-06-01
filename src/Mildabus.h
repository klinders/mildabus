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
#include <vector>

#define MASTER_ADDRESS 0x22
/**
 * @typedef MB_Error_Type
 * 
 */
typedef enum mb_error_type{
    MB_BUS_ERROR,               /*! MB_BUS_ERROR */
    MB_CLOCK_ERROR,             /*! MB_CLOCK_ERROR */
    MB_TRANSMIT_ERROR,          /*! MB_TRANSMIT_ERROR */
    MB_RECEIVE_ERROR,           /*! MB_BUS_ERROR */
    MB_ADRESS_COLLISION_ERROR,  /*! MB_ADRESS_COLLISION_ERROR */
    MB_CONFIG_ERROR             /*! MB_CONFIG_ERROR */
} MB_Error_Type;

/**
 * @typedef MB_Error
 * 
 */
typedef struct mb_error_struct{
    MB_Error_Type type;         /*! MB_Error_Type */
    uint32_t time;              /*! Current time */
} MB_Error;

class Mildabus
{
private:
    bool master_mode = false;
    bool active = false;
    uint32_t adress = 0x00;
    // Error Management (max 8 exceptions are saved )
    uint8_t error_count = 0;
    MB_Error error[8];
    void raise_exception(MB_Error_Type e);
public:
    /**
     * @brief Construct a new Mildabus object
     * 
     * @param can 
     * @param master 
     * @param adress 
     */
    Mildabus(CAN& can, bool master = false, uint16_t adress = 0x00);
    bool prepare(void);
    bool set_adress(uint16_t a);
    uint32_t register_self(void);
    bool transmit(uint16_t dest, uint8_t& data, int length);
    bool transmit_exceptions(void);
};

#endif
