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
#include "Error.h"
#include "Message.h"
#include "Filter.h"

#define MASTER_ADDRESS 0x22
#define ASSIGN_ADDRESS 0x02
#define ADDRESS_CONFIRM 0x34
#define DESTINATION_ALL 0x00

class Mildabus
{
private:
    CAN& can;
    bool master_mode;
    bool active;
    uint32_t address;
    // Error Management (max 8 exceptions are saved )
    uint8_t error_count;
    MB_Error error[8];
    uint32_t device_id;

    void raise_exception(MB_Error_Type e);
    bool transmit_exceptions(void);
    void request_address(bool blocking);
public:
    /**
     * @brief Construct a new Mildabus object
     * 
     * @param can 
     * @param master 
     * @param address 
     */
    Mildabus(CAN* can_o, bool master = false, uint16_t address = 0x00);
    bool prepare(void);
    bool set_address(uint16_t a);
    uint32_t register_self(void);
    bool write(MB_Message message);
    bool read(MB_Message &message, MB_Filter filter = MB_FILTER_NONE);
    void can_rx_handler(void);
    void can_tx_handler(void);
    void can_wu_handler(void);
};
#endif
