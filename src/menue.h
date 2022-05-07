#ifndef _MENUE_H_
#define _MENUE_H_
#include <LiquidCrystal.h>
#include <RTClib.h>
#include <string.h>
#include "constants.h"
#include "storage.h"
#include "relais.h"

class menue {
    private:
    LiquidCrystal myLcd;
    uint8_t myPos = 0, myEntryId = 0, mySingleValue = 0;
    bool myEntryDefined = false, myPosSelected = false;
    parameterSet mySet;

    relaisInterface *theRelaisInterface;
    RTC_DS3231 *theRTC;

    void homeScreen(void);

    void itemSelectionMenue(constants::inputSignal aSignal);
    void parameterSelectionMenue(constants::inputSignal aSignal);

    void statusMenue(constants::inputSignal aSignal);
    void durationMenue(constants::inputSignal aSignal);
    void startMenue(constants::inputSignal aSignal);
    void endMenue(constants::inputSignal aSignal);
    void dayMenue(constants::inputSignal aSignal);
    void matrixMenue(constants::inputSignal aSignal);
    void timeMenue(constants::inputSignal aSignal);
    void dateMenue(constants::inputSignal aSignal);
    void contrastMenue(constants::inputSignal aSignal);

    public:
    menue(relaisInterface *aRelaisInterface, RTC_DS3231 *aRTC);

    void changeState(bool aMenueState);
    void processSignal(constants::inputSignal aSignal);
    void update(void);
};

#endif