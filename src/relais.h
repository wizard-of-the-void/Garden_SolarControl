#ifndef _RELAIS_H_
#define _RELAIS_H_

#include <Arduino.h>
#include <RTClib.h>
#include "storage.h"

class relaisInterface {
    private: 
    //pointer to rtc-object
    RTC_DS3231 *myRtc;
    //array of shut off times for outputs
    DateTime myTimeStamps[8];
    
    //nuber of available outputs
    uint8_t myCount;
    //array of const for output pins
    const uint8_t *myOuts;
    //buffer for output state
    uint8_t outStates;
    //handles output inversion and buffer extraction
    void setOutput(uint8_t aOutput);
    //does output buffering
    bool setState(uint8_t aOutput, bool aState);

    //checks of parameter set
    bool checkDayOfWeek(uint8_t aDayOfWeekBitmap);
    bool checkTimeInterval(simpleTime aStart, simpleTime aEnd);

    //alert setup with rtc
    void setOutputAlert(uint8_t aOutput, uint8_t aDelay);
    void updateRtcAlert(void);

    public:
    //constructor
    relaisInterface(uint8_t aCount, const uint8_t *someOuts, RTC_DS3231 *aRtc);

    //direct interface (mostly for the menue)
    bool toggleState(uint8_t aOutput, uint8_t aDelay);
    bool getState(uint8_t aOutput);

    //interface for message loop
    bool processParameterSet(parameterSet aSet);
    bool processAlert();
};

#endif