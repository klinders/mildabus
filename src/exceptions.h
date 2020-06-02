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
#ifndef MB_EXCEPTIONS_H
#define MB_EXCEPTIONS_H

#include <stdint.h>

/**
 * @typedef MB_Error_Type
 * 
 */
typedef enum mb_error_type{
    MB_BUS_ERROR,               /*! MB_BUS_ERROR */
    MB_CLOCK_ERROR,             /*! MB_CLOCK_ERROR */
    MB_TRANSMIT_ERROR,          /*! MB_TRANSMIT_ERROR */
    MB_RECEIVE_ERROR,           /*! MB_BUS_ERROR */
    MB_ADDRESS_COLLISION_ERROR,  /*! MB_ADDRESS_COLLISION_ERROR */
    MB_CONFIG_ERROR             /*! MB_CONFIG_ERROR */
} MB_Error_Type;

/**
 * @typedef MB_Error
 * 
 */
typedef struct mb_error_struct{
    MB_Error_Type type;         /*! MB_Error_Type */
    uint32_t time;              /*! Current time */
    bool transmitted;           /*! Error has been transmitted on the bus */
} MB_Error;

#endif