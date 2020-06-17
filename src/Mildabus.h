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
#include "Subscription.h"
#include "mb_list.h"
#include "Device.h"
#include "Filter.h"
#include <stdint.h>

// Version of the Mildabus
#define VERSION_MAJOR	0
#define VERION_MINOR	0
#define VERIONS_PATCH	0 

// For STM32F4 devices...
#define FILTER_BANKS 28

/**
 * @brief Mildabus Object
 * 
 */
class Mildabus
{
private:
	// The CAN object to operate
	CAN* _can;

	// Is the Mildabus operating in Master Mode
	bool _master_mode;

	// Is the Mildabus Connected
	bool _active;

	// The MB Node Address
	uint8_t _address;

	// Subscriptions linked list
	MB_List<MB_Subscription*> _subscription_list[MB_Message::TYPE_COUNT];

	// Amount of errors
	uint8_t _error_count;

	// The Error array (past 8 errors)
	MB_Error _error[8];

	// The MB Node Device ID
	uint32_t _device_id;

	// A list of free filter banks
	MB_Filter _filter_list[FILTER_BANKS];
	bool _use_filters = false;

	uint32_t _timestamp;

	/**
	 * @brief Transmit all errors from the error array
	 * 
	 * @return true     Success
	 * @return false    Error (again...)
	 */
	bool _transmit_exceptions(void);

	/**
	 * @brief Request a NODE ID from the master
	 * 
	 * @param blocking 
	 */
	void _request_address(bool blocking);
	
	/**
	 * @brief Call all the callbacks of the subscriptions for this message.
	 * 
	 * @param msg   The recieved MB_Message.
	 */
	void _handle_subscriptions(MB_Message&);
	
	/**
	 * @brief The read handler
	 * 
	 */
	void _can_rx_handler(void);

	/**
	 * @brief The write handler (gets called on transmit or abort)
	 * 
	 */
	void _can_tx_handler(void);

	/**
	 * @brief The Wake-Up handler
	 * 
	 */
	void _can_wu_handler(void);
	
	/**
	 * @brief Handle all NMT messaged
	 * 
	 * @param m     Message
	 */
	void _nmt_handler(MB_Message& m);

	/**
	 * @brief Handle all DCNF messaged
	 * 
	 * @param m     Message
	 */
	void _dcnf_handler(MB_Message& m);

	/**
	 * @brief Remove an active filter
	 * 
	 * @param f MB_Filter object @see MB_Filter
	 */
	void _remove_filter(MB_Filter& f);

	/**
	 * @brief Add a filter (up to 28 filters can be assigned)
	 * 
	 * @param f	Filter object @see MB_Filter
	 * @return 	true Filter assigned
	 * @return 	false No free filter available
	 */
	bool _reserve_filter(MB_Filter& f);

	uint32_t _build_id(MB_Message::Type type, uint8_t id);

public:
	/**
	 * @brief Construct a new Mildabus object
	 * 
	 * @param rx        PinName for the RX pin
	 * @param tx        PinName for the TX pin
	 * @param master    [Operate in master mode]
	 * @param address   [Predefine a specific address]
	 */
	Mildabus(PinName rx, PinName tx, bool master = false, uint8_t address = 0x00);

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
	bool read(MB_Message& m, uint32_t handle);

	/**
	 * @brief Get all the subscriptions in the list
	 * 
	 * @param   t list to read from
	 * @return  std::list<MB_Subscription>&
	 */
	MB_List<MB_Subscription*>& getSubscriptions(MB_Message::Type t);

	/**
	 * @brief Add subscription
	 * 
	 * @param c     Callback
	 * @param t     [Type of incomming message]
	 * @param id    [Specific ID]
	 * @return MB_Subscription& 
	 */
	MB_Subscription* subscribe(
		Callback<void(MB_Message&)> c, 
		MB_Message::Type t = MB_Message::ALL,
		uint8_t id = 0);

	/**
	 * @brief Add subscription with Error filter
	 * 
	 * @param c     Callback
	 * @param t     Type of incomming message
	 * @param e     Type of error
	 * @param id    [Specific ID]
	 * @return MB_Subscription& 
	 */
	MB_Subscription* subscribe(
		Callback<void(MB_Message&)> c, 
		MB_Message::Type t, 
		MB_Error::Type e, 
		uint8_t id = 0);

	/**
	 * @brief Add subscription with Event filter
	 * 
	 * @param c     Callback
	 * @param t     Type of incomming message
	 * @param e     Type of event
	 * @param id    [Specific ID]
	 * @return MB_Subscription& 
	 */
	MB_Subscription* subscribe(
		Callback<void(MB_Message&)> c, 
		MB_Message::Type t, 
		MB_Event::Type e, 
		uint8_t id = 0);

	/**
	 * @brief remove subscription
	 * 
	 * @param s The subscription to remove
	 */
	void unsubscribe(MB_Subscription* s);

	/**
	 * @brief remove all subscription
	 * 
	 */
	void unsubscribeAll(void);

	/**
	 * @brief Get the Address
	 * 
	 * @return uint8_t 
	 */
	uint8_t getAddress(void) const{return _address;};

	/**
	 * @brief Get the Error Count
	 * 
	 * @return uint8_t 
	 */
	uint8_t getErrorCount(void) const{return _error_count;};

	/**
	 * @brief Get the Device ID
	 * 
	 * @return uint32_t 
	 */
	uint32_t getDeviceID(void) const{return _device_id;};

	/**
	 * @brief Get the Errors array
	 * 
	 * @return const MB_Error* const 
	 */
	const MB_Error* const getErrors(void) const{return _error;};

	/**
	 * @brief Check if the Mildabus is connected
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isActive(void) const{return _active;};

	/**
	 * @brief Check if the Mildabus is in Master Mode
	 * 
	 * @return true 
	 * @return false 
	 */
	bool isMaster(void) const{return _master_mode;};

	// Not implemented yet
	void enableFilters(void);
	void disableFilters(void);

};
#endif
