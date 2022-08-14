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

    //States representing the screens and linking to the
    //nessesary strings.
    enum class state:uint8_t {
                                none            = 255, 
                                home            =   0, 
                                selection       =   1, 
                                subSelection    =   2,  
                                elementStatus   =   3, 
                                elementDuration =   4, 
                                elementStart    =   5, 
                                elementEnd      =   6, 
                                elementDay      =   7, 
                                elementMatrix   =   8, 
                                contrast        =   9, 
                                time            =  10, 
                                date            =  11
                             };

    state myState, myOldState;
    LiquidCrystal myLcd;
    char myLines[constants::lcd_conf_rows][constants::lcd_conf_cols + 1] = {{ 0 }};
    uint8_t myPos = 0, myEntryId = 0, mySingleValue = 0;
    bool myEntryDefined = false, myPosSelected = false;
    parameterSet mySet;

    relaisInterface *theRelaisInterface;
    RTC_DS3231 *theRTC;

    void clearLineBuffer(void);
    void makeFirstLine(state aState);
    void makeSecondLine(state aState);

    // SCREENS
    void homeScreen(constants::inputSignal aSignal);

    // SELECTION-SCREENS
    void itemSelectionMenue(constants::inputSignal aSignal);
    void parameterSelectionMenue(constants::inputSignal aSignal);

    // SUB-SCREENS
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
    // Constructor
    menue(relaisInterface *aRelaisInterface, RTC_DS3231 *aRTC);

    // INTERFACE
    void changeState(bool aMenueState);
    void processSignal(constants::inputSignal aSignal);
    void setContrast(uint8_t aContrast);
};


#endif