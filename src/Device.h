#ifndef MB_DEVICES_H
#define MB_DEVICES_H

#include <stdint.h>

/**
 * @brief Mildabus Device Object
 * 
 */
class MB_Device{
public:
    /**
     * @brief Device Type
     * 
     */
    enum Type {
        MASTER = 0x00,
        NAVLIGHT = 0x01,
        LIGHT = 0x02,
        DASHBOARD = 0x03,
        VSENSE = 0x04,
        TSENSE = 0x05,
        PSENSE = 0x06,
        ISENSE = 0x07,
        LSENSE = 0x08,
        DOORSENSE = 0x09,
        LOCK = 0x0A,
        KEYPAD = 0x0B,
        NONE = 0xFF
    } type;

    /**
     * @brief Node ID
     * 
     */
    uint8_t id;

    /**
     * @brief Device ID
     * 
     */
    uint32_t device_id;
};
#endif