#ifndef _MENUE_H_
#define _MENUE_H_
#include <LiquidCrystal.h>
#include <string.h>
#include "constants.h"
#include "storage.h"

class menue {
    private:
    LiquidCrystal myLcd = LiquidCrystal(constants::lcd_rs, constants::lcd_en, 
                                      constants::lcd_d4, constants::lcd_d5, 
                                      constants::lcd_d6, constants::lcd_d7);
    uint8_t myPos = 0, myEntryId = 0, mySingleValue = 0;
    bool myEntryDefined = false, myPosSelected = false;
    parameterSet mySet;

    public:
    menue();

    void changeState(bool aMenueState);
    void processSignal(constants::inputSignal aSignal);
    void update(void);
};

#endif