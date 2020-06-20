# Mildabus
A very simple CAN bus-based communication protocol. The protocol defines communication between multiple nodes and a single master. The protocol is build on CAN2.0B implementing the 29 bit extended ID field.
The protocol is made for a plug-and-play experience including automatic ID assignment.

## Used platforms
The project is build upon Mbed-OS.

## Usage
```C++
// Example script with an LED
// Mildabus is initialised in test (loopback) mode so it receives its own messages.
// The LED will toggle once a second.
#include <mbed.h>
#include <Mildabus.h>

// Initialise the Mildabus
Mildabus milda1(CAN1_RX, CAN1_TX, /* MASTER = */ true, /* ID = */ 0, /* TEST_MODE = */ true);

// Event handler
void event(MB_Message&);

int main() {

    milda1.getConnected();
    // Attach a handler to a specific event
    milda1.subscribe(callback(&event), MB_Message::EVENT_TX, MB_Event::LIGHTS_ON);

	while(1) {
		// Send a message once a second.
		wait_ms(1000);
		milda1.send(MB_Event::LIGHTS_ON);
	}
}

void event(MB_Message& m){
    // Toggle your led
	Led.toggle();
} 

```

## License
[MIT](https://choosealicense.com/licenses/mit/)