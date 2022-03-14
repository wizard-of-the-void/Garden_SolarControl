#ifndef _SIGNAL_ROUTER_H_
#define _SIGNAL_ROUTER_H_

#include <RTClib.h>
#include <fifo.h>
#include <timerinterface.h>
#include <relais.h>
#include <signal.h>
#include "constants.h"

class signalRouter {
    private:
        timerInterface *theTimerInterface;
        relaisInterface *theRelaisInterface;

        uint8_t myInputs;
        uint8_t myOutputs;

        volatile FIFO<triggerSignal, 64> myBuffer;
        uint8_t *myMatrix;
        uint8_t myMenuFilter;
        bool myMenuFilterState;

    public:
        signalRouter(uint8_t aInputCount, uint8_t aOutputCount);
        ~signalRouter();

        bool attachOutput(uint8_t aInput, uint8_t aOutput);
        bool detachOutput(uint8_t aInput, uint8_t aOutput);
        bool isOutputAttached(uint8_t aInput, uint8_t aOutput);

        bool attachToMenue(uint8_t aInput);
        bool detachFromMenue(uint8_t aInput);
        bool isAttachedToMenue(uint8_t aInput);
        bool enableMenue(void);
        bool disableMenue(void);

        bool issueSignal(triggerSignal aSignal) volatile;
        bool runRouter(void);
};

#endif