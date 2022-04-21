#include "timerInterface.h"
#include "storage.h"
#include <Arduino.h>

timerInterface::timerInterface(RTC_DS3231 *aRtc) {
    myRtc = aRtc;
}

void timerInterface::updateStartTime(uint8_t aTimerIdx) {
    DateTime myNow = myRtc->now();
    if (myNow > myStartTimes[aTimerIdx]) {
        parameterSet mySet;
        getConfigTblPage(constants::timerPageOffset + aTimerIdx, mySet);
        uint8_t myWeekDay = myNow.dayOfTheWeek();
        myStartTimes[aTimerIdx] = DateTime(2000,01,01,00,00,00);
        for (uint8_t i = 0; i < 8; i++) {
            if (mySet.daysOfWeek & (0b00000001 << (myWeekDay + i)%7)) {
                myStartTimes[aTimerIdx] =   DateTime( 
                                                    myNow.year(), 
                                                    myNow.month(), 
                                                    myNow.day(), 
                                                    mySet.start.hour, 
                                                    mySet.start.minute, 
                                                    0
                                                    ) 
                                            + TimeSpan(i,0,0,0);
                if (myNow < myStartTimes[aTimerIdx]) {
                    return;
                } else {
                    myStartTimes[aTimerIdx] = DateTime(2000,01,01,00,00,00);
                }
            }
        }
    }
}

void timerInterface::updateRtcAlert(void) {

}
 
constants::inputSignal timerInterface::processInterrupt(void) {

}


