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

    enum class state:uint8_t {none, home, selection, subSelection, contrast, time, date, elementStatus, elementDuration, elementStart, elementEnd, elementDay, elementMatrix};
    state myState, myOldState;
    LiquidCrystal myLcd;
    uint8_t myPos = 0, myEntryId = 0, mySingleValue = 0;
    bool myEntryDefined = false, myPosSelected = false;
    parameterSet mySet;

    relaisInterface *theRelaisInterface;
    RTC_DS3231 *theRTC;

    // BASIC DISPLAY FUNCTIONS
    void makeCombinedLine(char* aTarget, const char* const firstPart, const char* const secondPart);
    void update(const uint8_t &l11, const uint8_t &l12, const uint8_t &l21);
    void makeFirstLine(const uint8_t &aElementIndex_A, const uint8_t &aElementIndex_B);
    void makeSecondLine(const uint8_t &aElementIndex);

    // SCREENS
    void homeScreen(constants::inputSignal aSignal);

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

    // INTERFACE
    void changeState(bool aMenueState);
    void processSignal(constants::inputSignal aSignal);
};

#endif