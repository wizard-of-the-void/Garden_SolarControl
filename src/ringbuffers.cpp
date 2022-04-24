#include "constants.h"
#include "ringbuffers.h"

void transfereIsrToMainRing(timerInterface* aTimerInterface) {
    uint8_t myLevel = isrRing::level();
    constants::inputSignal myValue = constants::inputSignal::nop;
    for (uint8_t i = 0; i < myLevel; i++) {
        myValue = isrRing::read();
        if (myValue == constants::inputSignal::timerIrq) {
            aTimerInterface->processInterrupt();
        }
        mainRing::write(myValue);
    }
}

void ring::writeToRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aWriteIndex, constants::inputSignal &aSignal) {
    aWriteIndex++;
    aWriteIndex %= aRingSize;
    aBuffer[aWriteIndex] = aSignal;
}

constants::inputSignal ring::readFromRing(const uint8_t &aRingSize, volatile constants::inputSignal* aBuffer, volatile uint8_t &aReadIndex) {
    aReadIndex++;
    aReadIndex %= aRingSize;
    constants::inputSignal mySignal = aBuffer[aReadIndex];
    aBuffer[aReadIndex] = constants::inputSignal::nop;
    return mySignal;
}

uint8_t ring::getRingLevel(const uint8_t &aRingSize, volatile uint8_t &aReadIndex,  volatile uint8_t &aWriteIndex) {
    if (aReadIndex <= aWriteIndex) {
        return aWriteIndex - aReadIndex;
    } else {
        return aRingSize - aReadIndex + aWriteIndex;
    }
}

//--------------------
//Main-Ring-Functions:
//--------------------
namespace mainRing {
    constants::inputSignal theBuffer[constants::mainRingBufferSize] = {constants::inputSignal::nop};
    uint8_t theWriteIndex = 0, theReadIndex = 0;
}

void mainRing::write(constants::inputSignal &aSignal) {
    ring::writeToRing(constants::mainRingBufferSize, theBuffer, theWriteIndex, aSignal);
}

constants::inputSignal mainRing::read(void) {
    return ring::readFromRing(constants::mainRingBufferSize, theBuffer, theReadIndex);
}

uint8_t mainRing::level(void) {
    return ring::getRingLevel(constants::mainRingBufferSize, theReadIndex, theWriteIndex);
}

//--------------------
//Isr-Ring-Functions:
//--------------------
namespace isrRing{
    constants::inputSignal volatile theBuffer[constants::isrRingBufferSize] = {constants::inputSignal::nop};
    uint8_t volatile theWriteIndex = 0, theReadIndex = 0;
}

void isrRing::write(constants::inputSignal &aSignal) {
    ring::writeToRing(constants::isrRingBufferSize, theBuffer, theWriteIndex, aSignal);
}

constants::inputSignal isrRing::read(void) {
    return ring::readFromRing(constants::isrRingBufferSize, theBuffer, theReadIndex);
}

uint8_t isrRing::level(void) {
    return ring::getRingLevel(constants::isrRingBufferSize, theReadIndex, theWriteIndex);
}    