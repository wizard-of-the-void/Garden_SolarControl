#ifndef _RINGBUFFERS_H_
#define _RINGBUFFERS_H_

#include "constants.h"
#include "timerInterface.h"

// setup input & ISR ring buffer
namespace mainRing {
    void write(constants::inputSignal &aSignal);    
    constants::inputSignal read(void);
    uint8_t level(void);
}

namespace isrRing {
    void write(constants::inputSignal &aSignal);
    constants::inputSignal read(void);
    uint8_t level(void);
}

void transfereIsrToMainRing(timerInterface* aTimerInterface);

namespace ring{
void writeToRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aWriteIndex, constants::inputSignal &aSignal);
constants::inputSignal readFromRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aReadIndex);
uint8_t getRingLevel(const uint8_t &aRingSize, volatile uint8_t &aReadIndex, volatile uint8_t &aWriteIndex);
}

#endif