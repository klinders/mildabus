# Mildabus
A very simple CAN bus-based communication protocol. The protocol defines communication between multiple nodes and a single master. The protocol is build on CAN2.0B implementing the 29 bit extended ID field.
The protocol is made for a plug-and-play experience including automatic ID assignment.

## Used platforms
The project is build upon Mbed-OS.

## Usage
```C++
#import <Mildabus.h>

CAN my_can_interface(PIN_RX, PIN_TX); // Create a can interface using the MBED CAN Class
Mildabus my_mildabus(my_can_interface [, MASTER] [, ADDRESS]) // Create a Mildabus and pass the MBED CAN operator.   

```

## License
[MIT](https://choosealicense.com/licenses/mit/)