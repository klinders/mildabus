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
#include "Subscription.h"
#include "list"
#include "Device.h"
#include <stdint.h>

/**
 * @brief Mildabus Object
 * 
 */
class Mildabus
{
private:
    // The CAN object to operate
    CAN& can;

    // Is the Mildabus operating in Master Mode
    bool master_mode;

    // Is the Mildabus Connected
    bool active;

    // The MB Node Address
    uint8_t address;

    // Subscriptions linked list
    std::list<MB_Subscription> subscription_list[sizeof(MB_Subscription::Type)/sizeof(MB_Subscription::ALL)];

    // Amount of errors
    uint8_t error_count;

    // The Error array (past 8 errors)
    MB_Error error[8];

    // The MB Node Device ID
    uint32_t device_id;

    /**
     * @brief Transmit all errors from the error array
     * 
     * @return true     Success
     * @return false    Error (again...)
     */
    bool transmitExceptions(void);

    /**
     * @brief Request a NODE ID from the master
     * 
     * @param blocking 
     */
    void requestAddress(bool blocking);
    
    /**
     * @brief Call all the callbacks of the subscriptions for this message.
     * 
     * @param msg   The recieved MB_Message.
     */
    void handle_subscriptions(MB_Message);
    
    /**
     * @brief The read handler
     * 
     */
    void can_rx_handler(void);

    /**
     * @brief The write handler (gets called on transmit or abort)
     * 
     */
    void can_tx_handler(void);

    /**
     * @brief The Wake-Up handler
     * 
     */
    void can_wu_handler(void);
public:
    /**
     * @brief Construct a new Mildabus object
     * 
     * @param can       The CAN object to operate with
     * @param master    [Operate in master mode]
     * @param address   [Predefine a specific address]
     */
    Mildabus(CAN* can_o, bool master = false, uint8_t address = 0x00);

    /**
     * @brief Destroy the Mildabus object
     * 
     */
    ~Mildabus();

    /**
     * @brief Connect to the Mildabus. If needed a new node ID is requested
     * 
     * @return true     Successfully connected
     * @return false    Error
     */
    bool getConnected(void);

    /**
     * @brief Raise an error (MB_Error object)
     * 
     * @param e     MB_Error object @see MB_Error
     */
    void raiseException(MB_Error::Type e);

    /**
     * @brief Send a message over the Mildabus
     * 
     * @param m         MB_Message to send
     * @return true     Success
     * @return false    Error
     */
    bool send(MB_Message m);

    /**
     * @brief Read a message from the Mildabus
     * 
     * @param m     A MB_Message reference. This reference will be filled 
     *              with the data from the Mildabus
     * @param f     [A filter to apply]
     * @return true 
     * @return false 
     */
    bool read(MB_Message& m, MB_Filter::Type f = MB_Filter::FILTER_NONE);

    /**
     * @brief Get all the subscriptions in the list
     * 
     * @param   t list to read from
     * @return  std::list<MB_Subscription>&
     */
    std::list<MB_Subscription>& getSubscriptions(MB_Subscription::Type t);

    /**
     * @brief Add subscription
     * 
     * @param c     Callback
     * @param t     [Type of incomming message]
     * @param d     [Type of device]
     * @param id    [Specific ID]
     * @return MB_Subscription& 
     */
    MB_Subscription& subscribe(
        Callback<void(MB_Message)> c, 
        MB_Subscription::Type t = MB_Subscription::ALL,
        MB_Device::Type d = MB_Device::NONE,
        uint8_t id = 0);

    /**
     * @brief Add subscription with Error filter
     * 
     * @param c     Callback
     * @param t     Type of incomming message
     * @param e     Type of error
     * @param d     [Type of device]
     * @param id    [Specific ID]
     * @return MB_Subscription& 
     */
    MB_Subscription& subscribe(
        Callback<void(MB_Message)> c, 
        MB_Subscription::Type t, 
        MB_Error::Type e, 
        MB_Device::Type d = MB_Device::NONE, 
        uint8_t id = 0);

    /**
     * @brief Add subscription with Event filter
     * 
     * @param c     Callback
     * @param t     Type of incomming message
     * @param e     Type of event
     * @param d     [Type of device]
     * @param id    [Specific ID]
     * @return MB_Subscription& 
     */
    MB_Subscription& subscribe(
        Callback<void(MB_Message)> c, 
        MB_Subscription::Type t, 
        MB_Event::Type e, 
        MB_Device::Type d = MB_Device::NONE, 
        uint8_t id = 0);

    /**
     * @brief remove subscription
     * 
     * @param s The subscription to remove
     */
    void unsubscribe(MB_Subscription& s);

    /**
     * @brief Get the Address
     * 
     * @return uint8_t 
     */
    uint8_t getAddress(void) const{return address;};

    /**
     * @brief Get the Error Count
     * 
     * @return uint8_t 
     */
    uint8_t getErrorCount(void) const{return error_count;};

    /**
     * @brief Get the Device ID
     * 
     * @return uint32_t 
     */
    uint32_t getDeviceID(void) const{return device_id;};

    /**
     * @brief Get the Errors array
     * 
     * @return const MB_Error* const 
     */
    const MB_Error* const getErrors(void) const{return error;};

    /**
     * @brief Check if the Mildabus is connected
     * 
     * @return true 
     * @return false 
     */
    bool isActive(void) const{return active;};

    /**
     * @brief Check if the Mildabus is in Master Mode
     * 
     * @return true 
     * @return false 
     */
    bool isMaster(void) const{return master_mode;};

    /**
     * @brief Handle all NMT messaged
     * 
     * @param m     Message
     */
    void nmtHandler(MB_Message m);

    /**
     * @brief Handle all DCNF messaged
     * 
     * @param m     Message
     */
    void dcnfHandler(MB_Message m);
};
#endif
