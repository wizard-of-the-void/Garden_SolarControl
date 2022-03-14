#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#include <RTClib.h>
#include <fifo.h>
#include <relais.h>
#include <router.h>
#include "constants.h"

class timerInterface {
    private:
        RTC_DS3231 myRtc;
        
        DateTime myDelays[4], myIntervals[7][2];
        uint8_t currentDelay, currentInterval[2];
        
        relaisInterface* theRelaisInterface;
        signalRouter* theSignalRouter;

        uint8_t findNextDelay();
        uint8_t* findNextInterval();

    public:
        timerInterface(signalRouter* aSignalRouter);

        bool setDelay(uint8_t aOutput);
        uint8_t getDelay(uint8_t aOutput);

        bool setIntervalStart(DateTime& aStart);
        DateTime getIntervalStart(DateTime& aStart);
        bool setIntervalEnd(DateTime& aEnd);
        DateTime getIntervalEnd(DateTime& aEnd);

        void processInterrupt(void);
        void programTimer(void);
};

#endif