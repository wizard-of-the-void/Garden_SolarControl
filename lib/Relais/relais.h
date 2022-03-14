#ifndef _RELAIS_H_
#define _RELAIS_H_

#include <inttypes.h>

class relaisInterface {
    private: 
    uint8_t myCount;
    const uint8_t *myOuts;
    uint8_t outStates;
    void setOutput(uint8_t aOutput);
    
    public:
    relaisInterface(uint8_t aCount, const uint8_t *someOuts);

    bool toggleState(uint8_t aOutput);
    bool setState(uint8_t aOutput, bool aState);
};

#endif