# Mildabus
A very simple CAN bus-based communication protocol. The protocol defines communication between multiple nodes and a single master. The protocol is build on CAN2.0B implementing the 29 bit extended ID field.
The protocol is made for a plug-and-play experience including automatic ID assignment.

## Used platforms
The project is build upon Mbed-OS.

## Usage
```C++
#import <mbed.h>
#import <Mildabus.h>
// Create a can interface using the MBED CAN Class
CAN my_can_interface(PIN_RX, PIN_TX);
// Create a Mildabus and pass the MBED CAN operator. 
Mildabus my_mildabus(my_can_interface [, MASTER] [, ADDRESS]);  

```

## License
[MIT](https://choosealicense.com/licenses/mit/)