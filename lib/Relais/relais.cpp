#include "relais.h"
#include <Arduino.h>

relaisInterface::relaisInterface(uint8_t aCount, const uint8_t *someOuts, RTC_DS3231 *aRtc) {
    myCount = aCount;
    myOuts = someOuts;
    outStates = 0x00;
    myRtc = aRtc;
}

bool relaisInterface::toggleState(uint8_t aOutput, uint8_t aDelay) {
    if (aOutput < myCount) {
        outStates ^= (1 << aOutput);
        setOutput(aOutput);
        if (outStates & (1 << aOutput)) {
            setOutputAlert(aOutput, aDelay);
            updateRtcAlert();
        }
        return outStates & (1 << aOutput);
    } else {
        return false;
    }
}

bool relaisInterface::setState(uint8_t aOutput, bool aState) {
    if (aOutput < myCount ) {
        if (aState) {
            outStates |= (1<<aOutput);
        } else {
            outStates &= ~(1 << aOutput);
        }
        setOutput(aOutput);
        return aState;
    } else {
        return false;
    }
}

bool relaisInterface::getState(uint8_t aOutput) {
    return outStates & (1 << aOutput);
}

void relaisInterface::setOutput(uint8_t aOutput) {
    bool myState = outStates & (1 << aOutput);
    digitalWrite(myOuts[aOutput], !myState);
}

bool relaisInterface::checkDayOfWeek(uint8_t aDayOfWeekBitmap){
    uint8_t myDay = (myRtc->now().dayOfTheWeek()+6)%7;
    return (aDayOfWeekBitmap & (0b00000001 << myDay));
}

bool relaisInterface::checkTimeInterval(simpleTime aStart, simpleTime aEnd){
    DateTime myNow = myRtc->now(), 
            myStart = DateTime(myNow.year(),myNow.month(), myNow.day(), aStart.hour, aStart.minute, 0), 
            myEnd = DateTime(myNow.year(),myNow.month(), myNow.day(), aEnd.hour, aEnd.minute, 0);
    
    if ( myStart == myEnd ) {
        return true;
    } else if ( myStart < myEnd ) {
        return ((myStart <= myNow) && (myNow <= myEnd));
    } else {
        return !((myEnd <= myNow) && (myNow <= myStart));
    }
}

void relaisInterface::setOutputAlert(uint8_t aOutput, uint8_t aDelay) {
    myTimeStamps[aOutput] = myRtc->now() + TimeSpan(0,0,aDelay,0);
}

void relaisInterface::updateRtcAlert(void) {
    DateTime myNow = myRtc->now(), myNextAlert = myNow + TimeSpan(1,0,0,0);
    for (uint8_t i = 0; i < myCount; i++) {
        if (getState(i)) {
            if (myNextAlert > myTimeStamps[i]) {
                myNextAlert = myTimeStamps[i];
            }
        }
    }
    myRtc->setAlarm2(myNextAlert, DS3231_A2_Hour);
}

bool relaisInterface::processParameterSet(parameterSet aSet) {
    //check if request needs to be processed
    if (aSet.state) {
        if (checkDayOfWeek(aSet.daysOfWeek)) {
            if (checkTimeInterval(aSet.start, aSet.end)) {
                for (uint8_t i = 0 ; i < myCount; i++) {
                    if (aSet.routingBitmap & (0b00000001 << i)) {
                        setState(i, true);
                        setOutputAlert(i, aSet.delay);
                    }
                }
                return true;
            }
        }
    }
    return false;
}

bool relaisInterface::processAlert(void) {
    DateTime myNow = myRtc->now();
    for (uint8_t i = 0; i < myCount; i++) {
        if (getState(i)) {
            if (myNow >= myTimeStamps[i]) {
                setState(i, false);
            }
        }
    }
    updateRtcAlert();
}
