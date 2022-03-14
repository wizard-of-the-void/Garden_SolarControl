#include <router.h>
#include <timerInterface.h>
#include <relais.h>

/*
class signalRouter {
    private:
        timerInterface *theTimerInterface;
        relaisInterface *theRelaisInterface;

        uint8_t myInputs;
        uint8_t myOutputs;

        volatile FIFO<triggerSignal, 64> myBuffer;
        uint8_t myMatrix[];
*/
signalRouter::signalRouter(uint8_t aInputCount, uint8_t aOutputCount) {
    if (aInputCount > 8) {
        myInputs = 8;
    } else {
        myInputs = aInputCount;
    }
    myOutputs = aOutputCount;
    myMatrix = new uint8_t[aOutputCount];
    theTimerInterface = new timerInterface(this);
    theRelaisInterface = new relaisInterface(aOutputCount);
    myMenuFilterState = false;
}

signalRouter::~signalRouter() {
    delete[] myMatrix;
    delete theTimerInterface;
    delete theRelaisInterface;
}

bool signalRouter::attachOutput(uint8_t aInput, uint8_t aOutput) {
    if ((aInput < myInputs) && (aOutput < myOutputs)) {
        myMatrix[aOutput] |= (1 << aInput);
        return true;
    } else {
        return false;
    }
}
    
bool signalRouter::detachOutput(uint8_t aInput, uint8_t aOutput) {
    if ((aInput < myInputs) && (aOutput < myOutputs)) {
        myMatrix[aOutput] &= ~(1 << aInput);
        return true;
    } else {
        return false;
    }
}
    
bool signalRouter::isOutputAttached(uint8_t aInput, uint8_t aOutput) {
    if ((aInput < myInputs) && (aOutput < myOutputs)) {
        return bool(myMatrix[aOutput] & (1 << aInput));
    } else {
        return NULL;
    }
}

bool signalRouter::attachToMenue(uint8_t aInput) {
    if (aInput < myInputs) {
        myMenuFilter |= (1 << aInput);
        return true;
    } else {
        return false;
    }
}

bool signalRouter::detachFromMenue(uint8_t aInput) {
    if (aInput < myInputs) {
        myMenuFilter &= ~(1 << aInput);
        return true;
    } else {
        return false;
    }
}

bool signalRouter::isAttachedToMenue(uint8_t aInput) {
    if (aInput < myInputs) {
        return bool(myMenuFilter & (1 << aInput));
    } else {
        return NULL;
    }
}

bool signalRouter::enableMenue(void) {
    myMenuFilterState = true;
}

bool signalRouter::disableMenue(void) {
    myMenuFilterState = false;
}

bool signalRouter::issueSignal(triggerSignal aSignal) volatile {
    myBuffer.push(aSignal);
}

bool signalRouter::runRouter(void) {
    triggerSignal mySignal();
    while (myBuffer.size() > 0) {

    }
}
