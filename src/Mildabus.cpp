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
#include "Mildabus.h"
#include <mbed.h>
#include "mb_list.h"

// Device Unique ID
uint32_t *uid = (uint32_t *)UID_BASE;

Mildabus::Mildabus(PinName rx, PinName tx, bool master, uint8_t addr)
    :_master_mode(master)
{
    _can = new CAN(rx,tx);
    //l.push_back();
    if(!_can->frequency(500000)){
        raiseException(MB_Error::CLOCK_ERROR);
        return;
    }
    
    if(!_can->mode(CAN::Normal)){
        raiseException(MB_Error::BUS_ERROR);
        return;
    }

    _device_id = ((uid[0]^uid[1])^uid[2])&0x00FFFFFF; // Xor to join and truncate 4 bits

    if(master){
        _address = MASTER_ADDRESS;
    }else if(addr){
        _address = addr;
    }
}

Mildabus::~Mildabus(){
    delete _can;
    unsubscribeAll();
}

bool Mildabus::getConnected(void){

    _can->reset();

    if(!_address){
        _request_address(true); // Request and block
    }

    // Setup the interupt handlers
    _can->attach(callback(this, &Mildabus::_can_rx_handler), CAN::RxIrq); // Received
    _can->attach(callback(this, &Mildabus::_can_tx_handler), CAN::TxIrq); // Transmitted or aborted
    _can->attach(callback(this, &Mildabus::_can_wu_handler), CAN::WuIrq); // Wake Up

    // Setup the bare subscriptions
    subscribe(callback(this, &Mildabus::_nmt_handler), MB_Subscription::NMT);
    subscribe(callback(this, &Mildabus::_dcnf_handler), MB_Subscription::DCNF);

    return true;
}

void Mildabus::_request_address(bool blocking){
    MB_Message msg;

    // Reset the MB address if one is there.    
    _address = 0;

    send(msg);
    // Block until the address is filled
    if(blocking) while(!_address);
}

void Mildabus::raiseException(MB_Error::Type e){
    MB_Error err;
    err.type = e;
    // TO DO: Setup systick/rtc
    err.time = 0;
    _error[_error_count] = err;
    // Transmit the fault if the bus is active
    if(_active){
        _transmit_exceptions();
    }

    //can.filter();

    // Raise the counter
    if(_error_count < 7) {
        _error_count++;
    }else{
        // Roll over
        _error_count = 0;
    }
}

bool Mildabus::send(MB_Message msg){
    return true;
}

bool Mildabus::read(MB_Message& message, MB_Filter::Type filter){
    int handle = 0;

    if(filter != MB_Filter::FILTER_NONE){
        // TBD
    }

    // A MB_Message for the incomming data (true for incomming)
    MB_Message msg;

    if(!_can->read(msg, handle)) return false;
    
    return true;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message&)> c, MB_Subscription::Type sub_type, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, MB_Error::NONE, MB_Event::NONE, id);
    subscription->attach(c);
    _subscription_list[sub_type].push_back(subscription);
    return subscription;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message&)> c, MB_Subscription::Type sub_type, MB_Event::Type e, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, MB_Error::NONE, e, id);
    subscription->attach(c);
    _subscription_list[sub_type].push_back(subscription);
    return subscription;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message&)> c, MB_Subscription::Type sub_type, MB_Error::Type e, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, e, MB_Event::NONE, id);
    subscription->attach(c);
    _subscription_list[sub_type].push_back(subscription);
    return subscription;
}

void Mildabus::unsubscribe(MB_Subscription* sub){
    // Removing the pointer from the list
    _subscription_list[sub->type].remove(sub);
    // Deleting the object from the heap
    delete sub;
}

void Mildabus::unsubscribeAll(){

}

void Mildabus::_handle_subscriptions(MB_Message& msg){
    // Convert the message type to sub type
    MB_Subscription::Type s_type = MB_Subscription::typeFromMessage(msg);
    if(s_type == MB_Subscription::NONE) return;
    // First do all the message specific subs
    MB_List<MB_Subscription*>& l = _subscription_list[s_type];

    // For each element in the list
    for(MB_Subscription* el : l){
        el->call(msg);
    }

    // For the "ALL" subscriptions
    MB_List<MB_Subscription*>& all_l = _subscription_list[MB_Subscription::ALL];

    // For each element in the list
    for(MB_Subscription* el : all_l){
        el->call(msg);
    }
}

bool Mildabus::_transmit_exceptions(void){
    // Nothing yet
    return true;
}

/***    Handlers    ***/

void Mildabus::_can_rx_handler(void){
    MB_Message message;
    if(read(message)){

    }
}

void Mildabus::_can_tx_handler(void){

}

void Mildabus::_can_wu_handler(void){

}

void Mildabus::_nmt_handler(MB_Message& m){
    
}

void Mildabus::_dcnf_handler(MB_Message& m){

}