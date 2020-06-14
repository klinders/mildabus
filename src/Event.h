#ifndef MB_EVENT_H
#define MB_EVENT_H

/**
 * @struct Mildabus Event Object
 * 
 */
struct MB_Event{
    // Event Type
    enum Type {
        NONE = 0x00
    } type;
};

#endif