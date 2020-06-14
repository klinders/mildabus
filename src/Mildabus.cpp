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

// Device Unique ID
uint32_t *uid = (uint32_t *)UID_BASE;

Mildabus::Mildabus(CAN* can_o, bool master, uint8_t addr):can(*can_o)
{
    if(!can.frequency(500000)){
        raiseException(MB_Error::CLOCK_ERROR);
        return;
    }
    
    if(!can.mode(CAN::Normal)){
        raiseException(MB_Error::BUS_ERROR);
        return;
    }

    device_id = ((uid[0]^uid[1])^uid[2])&0x00FFFFFF; // Xor to join and truncate 4 bits

    if(master){
        address = MASTER_ADDRESS;
    }else if(addr){
        address = addr;
    }
    master_mode = master;
}

Mildabus::~Mildabus(){
    size_t size = sizeof(MB_Subscription::Type)/sizeof(MB_Subscription::ALL);
    for(uint i = 0; i < size;i++){
        subscription_list[i].clear();
    }
}

bool Mildabus::getConnected(void){

    can.reset();

    if(!address){
        requestAddress(true); // Request and block
    }

    // Setup the interupt handlers
    can.attach(callback(this, &Mildabus::can_rx_handler), CAN::RxIrq); // Received
    can.attach(callback(this, &Mildabus::can_tx_handler), CAN::TxIrq); // Transmitted or aborted
    can.attach(callback(this, &Mildabus::can_wu_handler), CAN::WuIrq); // Wake Up

    // Setup the bare subscriptions
    subscribe(callback(this, &Mildabus::nmtHandler), MB_Subscription::NMT);
    subscribe(callback(this, &Mildabus::dcnfHandler), MB_Subscription::DCNF);

    return true;
}

void Mildabus::requestAddress(bool blocking){
    MB_Message msg;

    // Reset the MB address if one is there.    
    address = 0;

    send(msg);
    // Block until the address is filled
    if(blocking) while(!address);
}

void Mildabus::raiseException(MB_Error::Type e){
    MB_Error err;
    err.type = e;
    // TO DO: Setup systick/rtc
    err.time = 0;
    error[error_count] = err;
    // Transmit the fault if the bus is active
    if(active){
        transmitExceptions();
    }

    //can.filter();

    // Raise the counter
    if(error_count < 7) {
        error_count++;
    }else{
        // Roll over
        error_count = 0;
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

    if(!can.read(msg, handle)) return false;
    
    return true;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message)> c, MB_Subscription::Type sub_type, MB_Device::Type d, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, MB_Error::NONE, MB_Event::NONE, d, id);
    subscription->cb = c;
    subscription_list[sub_type].push_back(subscription);
    return subscription;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message)> c, MB_Subscription::Type sub_type, MB_Event::Type e, MB_Device::Type d, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, MB_Error::NONE, e, d, id);
    subscription->cb = c;
    subscription_list[sub_type].push_back(subscription);
    return subscription;
}

MB_Subscription* Mildabus::subscribe(Callback<void(MB_Message)> c, MB_Subscription::Type sub_type, MB_Error::Type e, MB_Device::Type d, uint8_t id)
{
    // Be warned! This is going to the heap
    MB_Subscription* subscription = new MB_Subscription(sub_type, e, MB_Event::NONE, d, id);
    subscription->cb = c;
    subscription_list[sub_type].push_back(subscription);
    return subscription;
}

void Mildabus::unsubscribe(MB_Subscription* sub){
    // Removing the pointer from the list
    subscription_list[sub->type].remove(sub);
    // Deleting the object from the heap
    delete sub;
}

void Mildabus::handle_subscriptions(MB_Message msg){
    // First do all the message specific subs
    std::list<MB_Subscription*> li = subscription_list[msg.type];

    std::list<MB_Subscription*>::iterator it;
    // For all subscriptions, call the callback
    for(it = li.begin();it != li.end();++it){
        (*it)->call(msg);
    }

    // For the "ALL" subscriptions
    std::list<MB_Subscription*> all_li = subscription_list[MB_Subscription::ALL];

    std::list<MB_Subscription*>::iterator all_it;
    // For all subscriptions, call the callback
    for(all_it = all_li.begin();all_it != all_li.end();++all_it){
        (*all_it)->call(msg);
    }
}

bool Mildabus::transmitExceptions(void){
    // Nothing yet
    return true;
}

/***    Handlers    ***/

void Mildabus::can_rx_handler(void){
    MB_Message message;
    if(read(message)){

    }
}

void Mildabus::can_tx_handler(void){

}

void Mildabus::can_wu_handler(void){

}

void Mildabus::nmtHandler(MB_Message m){
    
}

void Mildabus::dcnfHandler(MB_Message m){

}