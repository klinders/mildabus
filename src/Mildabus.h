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
#include "Subscriptions.h"
#include "list"
#include "Devices.h"

class Mildabus
{
private:
    CAN& can;
    bool master_mode;
    bool active;
    uint8_t address;

    // Subscriptions linked list
    std::list<MB_Subscription> subsciption_list;

    // Error Management (max 8 exceptions are saved )
    uint8_t error_count;
    MB_Error error[8];
    uint32_t device_id;

    bool transmitExceptions(void);
    void requestAddress(bool blocking);
    void can_rx_handler(void);
    void can_tx_handler(void);
    void can_wu_handler(void);
public:
    /**
     * @brief Construct a new Mildabus object
     * 
     * @param can 
     * @param master 
     * @param address 
     */
    Mildabus(CAN* can_o, bool master = false, uint8_t address = 0x00);
    ~Mildabus();
    bool getConnected(void);
    bool setAddress(uint16_t addr);
    void raiseException(MB_Error::Type e);
    bool send(MB_Message message);
    bool read(MB_Message &message, MB_Filter filter = MB_Filter());

    std::list<MB_Subscription>& getSubscriptions(void);
    void subscribe(Callback<void(MB_Message)> callback, MB_Subscription::Type trigger, MB_Filter = MB_Filter());
    void unsubscribe();

    uint8_t getAddress(void) const{return address;};
    uint8_t getErrorCount(void) const{return error_count;};
    uint32_t getDeviceID(void) const{return device_id;};
    const MB_Error* const getErrors(void) const{return error;};
    bool isActive(void) const{return active;};
    bool isMaster(void) const{return master_mode;};
};
#endif
