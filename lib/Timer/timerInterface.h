#ifndef _TIMER_INTERFACE_H_
#define _TIMER_INTERFACE_H_

#include <RTClib.h>
#include "constants.h"

class timerInterface {
    private:
        RTC_DS3231 *myRtc;
        
        DateTime myStartTimes[constants::timerCount];
        uint8_t activeTimer;
        
        void updateStartTime(uint8_t aTimerIdx);

    public:
        timerInterface(RTC_DS3231 *aRtc);

        void updateRtcAlert(void);
        constants::inputSignal processInterrupt(void);
};

#endif