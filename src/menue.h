#ifndef _MENUE_H_
#define _MENUE_H_

#include <Arduino.h>
#include <LiquidCrystal.h>
#include <RTClib.h>
#include "constants.h"

class durationObj {
    public:
        virtual uint8_t getDuration(uint8_t aIdx) = 0;
        virtual void setDuration(uint8_t aIdx, uint8_t aDuration) = 0;
};

class timeObj {
    public:
        virtual DateTime getDateTime(uint8_t aIdx) = 0;
        virtual void setDateTime(uint8_t aIdx, DateTime aDateTime) = 0;
};

class multiStateObj {
    public:
        virtual bool getState(uint8_t aIdx) = 0;
        virtual void setState(uint8_t aIdx, bool aState) = 0;
        virtual uint8_t stateCount(void) = 0;
};

class valueObj {
    public:
        virtual uint8_t getValue(void) = 0;
        virtual void setValue(uint8_t aValue) = 0;
};

class testObj : public durationObj, public timeObj, public multiStateObj, public valueObj {
    public:
        void setDuration(uint8_t aIdx, uint8_t aDuration);
        void setDateTime(uint8_t aIdx, DateTime aDateTime);
        void setState(uint8_t aIdx, bool aState);
        void setValue(uint8_t aValue);

        uint8_t getDuration(uint8_t aIdx);
        DateTime getDateTime(uint8_t aIdx);
        bool getState(uint8_t aIdx);
        uint8_t getValue(void);

        uint8_t stateCount(void);
};

class screen {
    private:    
        char    myFirstLine[constants::lcd_conf_cols+1],
                mySecondLine[constants::lcd_conf_cols+1];
        screen  *myParentScreen, *myPervScreen, *myNextScreen, *myChildScreen;
        static LiquidCrystal* myLcd; 
    public:
   
        enum class screenRelation:uint8_t {parent, child, previous, next};
        screen(LiquidCrystal *aLcd, const char* aFirstLine, const char* aSecondLine);
        screen(const char* aFirstLine, const char* aSecondLine);

        void setLinks(screen *parentScreen, screen *pervScreen, screen *nextScreen, screen *childScreen);
        screen* getScreen(screenRelation aRelation);
        void initText(bool showCursor);
        void updateChar(uint8_t aPos, char aChar);
        void updateLine(char* aLine);
        void setCursor(uint8_t aPos);
        void activate(void);
        virtual screen* receiveSignal(uint8_t aSignal) = 0;
};

class menue{
    private:
       LiquidCrystal myLcd;
       screen* myActiveScreen;
    public:
        menue(screen* aInitScreen);
        void displayOn(void);
        void displayOff(void);
        void reactToSignal(uint8_t aSignal);
};

class mainScreen : public screen {
    private: 

    public:
        mainScreen(void);
        screen* receiveSignal(uint8_t aSignal);
};

class selectionScreen : public screen{
    private:
        static constexpr const char* secondLine = "W  Z  #  E  => M";
    public:
        selectionScreen(const char* firstLine);
        screen* receiveSignal(uint8_t aSignal);
};

class durationScreen : public screen {
    private:
        durationObj* myDurationTarget;
        static constexpr const char* secondLine = "W  Z  +  -  => M";        
    public:
        durationScreen(const char* firstLine, durationObj* aDurationObj);
        screen* receiveSignal(uint8_t aSignal);

};

class stateScreen : public screen {
    private:
        multiStateObj* myStateTarget;
        static constexpr const char* secondLine = "#  #  +  -  => M";        
    public:
        stateScreen(const char* firstLine, multiStateObj* aMultiStateObj);
        screen* receiveSignal(uint8_t aSignal);
};

class multiStateScreen : public screen {
    private:
        multiStateObj* myMultiStateTarget;
        static constexpr const char* secondLine = "W  Z  +  -  => M";        
    public:
        multiStateScreen(const char* firstLine, multiStateObj* aMultiStateObj);
        screen* receiveSignal(uint8_t aSignal);
};

class dateScreen : public screen {
    private:
        timeObj* myDateTarget;
        static constexpr const char* secondLine = "W  Z  +  -  => M";        
    public:
        dateScreen(const char* firstLine, timeObj* aTimeObj);
        screen* receiveSignal(uint8_t aSignal);
};

class timeScreen : public screen {
    private:
        timeObj* myTimeTarget;
        static constexpr const char* secondLine = "W  Z  +  -  => M";        
    public:
        timeScreen(const char* firstLine, timeObj* aTimeObj);
        screen* receiveSignal(uint8_t aSignal);
};

class barScreen : public screen{
    private:
        valueObj* myValueObj;
        static constexpr const char* secondLine = "#  #  +  -  => M";        
    public:
        barScreen(const char* firstLine, valueObj* aValueObj);
        screen* receiveSignal(uint8_t aSignal);
};


/*       0123456789ABCDEF
str =   "TT DD.MM.  00:00"  => MainScreen
str =   "1=1 2=0  3=0 4=0"

        "Zschltg aendern?"  => SeclectionScreen 2
        "Matrix  aendern?"  => SeclectionScreen 2
        "Uhrzeit aendern?"  => SeclectionScreen 2
        "Datum   aendern?"  => SeclectionScreen 2
        "Kontrst aendern?"  => SeclectionScreen 2

        "Max-Ein: ### Min"  => DurationScreen 2
        "Bw1-Ein: ### Min"  => DurationScreen 2
        "Bw2-Ein: ### Min"  => DurationScreen 2

        "Bw1-Str-Z: ##:##"  => TimeScreen 2
        "Bw1-End-Z: ##:##"  => TimeScreen 2
        
        "Bw2-Str-Z: ##:##"  => TimeScreen 2
        "Bw2-End-Z: ##:##"  => TimeScreen 2

        "Ts1-Ein: ### Min"  => DurationScreen 2
        "Ts2-Ein: ### Min"  => DurationScreen 2

        "Z1-Status:   EIN"  => StateScreen 2
        "Z1-Str-Z:  ##:##"  => TimeScreen 2
        "Z1-End-Z:  ##:##"  => TimeScreen 2
        "Z1-WTage:1234567"  => DayScreen 2
        
        "Z2-Status:   EIN"  => StateScreen 2
        "Z2-Str-Z:  ##:##"  => TimeScreen 2
        "Z2-End-Z:  ##:##"  => TimeScreen 2
        "Z2-WTage:1234567"  => DayScreen 2

        "Bw1 => A:1 2 3 4"  => MatrixScreen 2
        "Bw2 => A:1 2 3 4"  => MatrixScreen 2
        "Ts1 => A:1 2 3 4"  => MatrixScreen 2
        "Ts2 => A:1 2 3 4"  => MatrixScreen 2
        "Z1  => A:1 2 3 4"  => MatrixScreen 2
        "Z2  => A:1 2 3 4"  => MatrixScreen 2

        "Zeit:      00:00"  => TimeScreen 2

        "Datum DD.MM.YYYY"  => DateScreen 2
        
        "0------|-------9"  => BarScreen 2

        "W  Z  #  E  => M"  => SeclectionScreen
        "W  Z  A  E  => M"  => DayScreen
        "W  Z  +  -  => M"  => DurationScreen, TimeScreen, DateScreen
        "#  #  +  -  => M"  => BarScreen, StateScreen            
        "1  2  3  4  => M"  => MatrixScreen
*/

#endif