#include "constants.h"
#include "ringbuffers.h"

void transfereIsrToMainRing(void) {
    uint8_t myLevel = isrRing::level();
    constants::inputSignal myValue = constants::inputSignal::nop;
    for (uint8_t i = 0; i < myLevel; i++) {
        myValue = isrRing::read();
        mainRing::write(myValue);
    }
}

void inline writeToRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aWriteIndex, constants::inputSignal &aSignal) {
    aWriteIndex++;
    aWriteIndex %= aRingSize;
    aBuffer[aWriteIndex] = aSignal;
}

constants::inputSignal inline readFromRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aReadIndex) {
    aReadIndex++;
    aReadIndex %= aRingSize;
    constants::inputSignal mySignal = aBuffer[aReadIndex];
    aBuffer[aReadIndex] = constants::inputSignal::nop;
    return mySignal;
}

uint8_t inline getRingLevel(const uint8_t &aRingSize, volatile uint8_t &aReadIndex,  volatile uint8_t &aWriteIndex) {
    if (aReadIndex <= aWriteIndex) {
        return aWriteIndex - aReadIndex;
    } else {
        return aRingSize - aReadIndex + aWriteIndex;
    }
}

//--------------------
//Main-Ring-Functions:
//--------------------
void inline mainRing::write(constants::inputSignal &aSignal) {
    ::writeToRing(constants::mainRingBufferSize, theBuffer, theWriteIndex, aSignal);
}

constants::inputSignal inline mainRing::read(void) {
    return ::readFromRing(constants::mainRingBufferSize, theBuffer, theReadIndex);
}

uint8_t inline mainRing::level(void) {
    return ::getRingLevel(constants::mainRingBufferSize, theReadIndex, theWriteIndex);
}

//--------------------
//Isr-Ring-Functions:
//--------------------
void inline isrRing::write(constants::inputSignal &aSignal) {
    ::writeToRing(constants::isrRingBufferSize, theBuffer, theWriteIndex, aSignal);
}

constants::inputSignal inline isrRing::read(void) {
    return ::readFromRing(constants::isrRingBufferSize, theBuffer, theReadIndex);
}

uint8_t inline isrRing::level(void) {
    return ::getRingLevel(constants::isrRingBufferSize, theReadIndex, theWriteIndex);
}    