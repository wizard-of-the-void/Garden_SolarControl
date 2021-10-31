#ifndef _RELAIS_H_
#define _RELAIS_H_

#include <inttypes.h>

class relaisInterface {
    private: 
    uint8_t armStates;
    uint8_t outStates;
    void setOutput(uint8_t aOutput);
    

    public:
    relaisInterface(void);
    void armOutput(uint8_t aOutput);
    void disarmOutput(uint8_t aOutput);
    bool protectedToggleState(uint8_t aOutput);
    bool toggleState(uint8_t aOutput);
    bool setState(uint8_t aOutput, bool aState);
};

#endif