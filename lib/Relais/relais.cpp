#include "relais.h"
#include "constants.h"
#include <Arduino.h>

relaisInterface::relaisInterface(void) {
    armStates = 0x00;
    outStates = 0x00;
}

void relaisInterface::armOutput(uint8_t aOutput) {
    armStates |= (1 << aOutput);
}

void relaisInterface::disarmOutput(uint8_t aOutput) {
    armStates &= ~(1 << aOutput);
}

void relaisInterface::protectedToggle(uint8_t aOutput) {
    bool myArmState = armStates & (1 << aOutput);
    if (myArmState) {
        directToggle(aOutput);
    }
}

void relaisInterface::directToggle(uint8_t aOutput) {
    outStates ^= (1 << aOutput);
    setOutput(aOutput);
}

void relaisInterface::direct(uint8_t aOutput, bool aState) {
    if (aState) {
        outStates |= (1<<aOutput);
    } else {
        outStates &= ~(1 << aOutput);
    }
    setOutput(aOutput);
}

void relaisInterface::setOutput(uint8_t aOutput) {
    bool myState = outStates & (1 << aOutput);
    digitalWrite(relay_out[aOutput], !myState);
}