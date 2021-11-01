#include "relais.h"
#include "constants.h"
#include <Arduino.h>

relaisInterface::relaisInterface(uint8_t aCount) {
    myCount = aCount;
    outStates = 0x00;
}

bool relaisInterface::toggleState(uint8_t aOutput) {
    if (aOutput < myCount) {
        outStates ^= (1 << aOutput);
        setOutput(aOutput);
        return outStates & (1 << aOutput);
    } else {
        return false;
    }
}

bool relaisInterface::setState(uint8_t aOutput, bool aState) {
    if (aOutput < myCount ) {
        if (aState) {
            outStates |= (1<<aOutput);
        } else {
            outStates &= ~(1 << aOutput);
        }
        setOutput(aOutput);
        return aState;
    } else {
        return false;
    }
}

void relaisInterface::setOutput(uint8_t aOutput) {
    bool myState = outStates & (1 << aOutput);
    digitalWrite(relay_out[aOutput], !myState);
}