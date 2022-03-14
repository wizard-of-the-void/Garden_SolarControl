#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#include <timerInterface.h>
#include <Adafruit_MCP23X17.h>
#include <router.h>
#include "constants.h"

class triggerSignal {
    private:
    uint8_t mySource;
    DateTime myCreation;
    uint8_t myDelay;

    public:
    triggerSignal(uint8_t aSource, uint8_t aDelay, DateTime aCreation);
    const uint8_t get_source(void);
    const DateTime get_creation(void);
    const uint8_t get_Delay(void);
    const DateTime get_expiration(void);
};

class signalInterface {
    private:
        Adafruit_MCP23X17 myMcp;
        timerInterface *theTimerInterface;
        signalRouter *theRouter;
        uint8_t myDelays[8];
    public:
        signalInterface(signalRouter *aRouter);
        void checkInputs(void);
        bool setDelay(uint8_t aInput);
};

#endif