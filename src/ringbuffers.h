#ifndef _RINGBUFFERS_H_
#define _RINGBUFFERS_H_

#include "constants.h"

// setup input & ISR ring buffer
namespace mainRing {
    constants::inputSignal theBuffer[constants::mainRingBufferSize] = {constants::inputSignal::nop};
    uint8_t theWriteIndex = 0, theReadIndex = 0;

    void inline write(constants::inputSignal &aSignal);    
    constants::inputSignal inline read(void);
    uint8_t inline level(void);
}

namespace isrRing {
    constants::inputSignal volatile theBuffer[constants::isrRingBufferSize] = {constants::inputSignal::nop};
    uint8_t volatile theWriteIndex = 0, theReadIndex = 0;

    void inline write(constants::inputSignal &aSignal);
    constants::inputSignal inline read(void);
    uint8_t inline level(void);
}

void transfereIsrToMainRing(void);
void inline writeToRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aWriteIndex, constants::inputSignal &aSignal);
constants::inputSignal inline readFromRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aReadIndex);
uint8_t inline getRingLevel(const uint8_t &aRingSize, volatile uint8_t &aReadIndex, volatile uint8_t &aWriteIndex);

#endif