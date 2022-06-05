//                                0123456789ABCDEF 
#include "menue.h"

menue::menue(relaisInterface *aRelaisInterface, RTC_DS3231 *aRTC):myLcd(constants::lcd_rs, constants::lcd_en, 
                        constants::lcd_d4, constants::lcd_d5, 
                        constants::lcd_d6, constants::lcd_d7) {
    theRelaisInterface = aRelaisInterface;
    theRTC = aRTC;
    myLcd.begin(16, 2);
    myState = state::home;
    myOldState = state::none;
}

void menue::makeCombinedLine(char* aTarget, const char* const firstPart, const char* const secondPart) {
    memset(aTarget, 0, constants::lcd_conf_cols + 1);
    strcat(aTarget, firstPart);
    strcat(aTarget, secondPart);
}

void menue::changeState(bool aMenueState) {
    if (aMenueState) {
        myLcd.clear();
        myLcd.display();
        myPos = 0;
        myEntryId = 0;
        myPosSelected = false;
        myEntryDefined = false;
        myState = state::home;
        myOldState = state::none;
        homeScreen(constants::inputSignal::nop);
    } else {
        myLcd.clear();
        myLcd.noDisplay();
        myPos = 0;
        myEntryId = 0;
        myPosSelected = false;
        myEntryDefined = false;
    }
}

void menue::processSignal(constants::inputSignal aSignal) {
    switch (myState) {
        case state::home:
            homeScreen(aSignal);
            break;
        case state::selection:
            itemSelectionMenue(aSignal);
            break;
        case state::subSelection:
            parameterSelectionMenue(aSignal);
            break;
        case state::contrast:
            contrastMenue(aSignal);
            break;
        case state::time:
            timeMenue(aSignal);
            break;       
        case state::date:
            dateMenue(aSignal);
            break;             
        case state::elementStatus:
            statusMenue(aSignal);
            break;      
        case state::elementDuration:
            durationMenue(aSignal);
            break;
        case state::elementStart:
            startMenue(aSignal);
            break;      
        case state::elementEnd:
            endMenue(aSignal);
            break;            
        case state::elementDay:
            dayMenue(aSignal);
            break;             
        case state::elementMatrix:
            matrixMenue(aSignal);
            break;                                         
    }
}


void menue::update(const uint8_t &l11, const uint8_t &l12, const uint8_t &l21) {
    if (myState != myOldState) {
        char myFirstLine[17] = {""}, mySecondLine[17] = {""};
        strcat(mySecondLine, constants::lcdContent::lables[0]);
        makeCombinedLine(myFirstLine,constants::lcdContent::names[myEntryId],constants::lcdContent::menue[0]);
        myLcd.setCursor(0,0);
        myLcd.println(myFirstLine);
        myLcd.println(mySecondLine);
    }
}


void menue::homeScreen(constants::inputSignal aSignal) {
    update(0,0,0);
    myOldState = state::home;
    switch (aSignal) {
        case constants::inputSignal::keyA:
        case constants::inputSignal::keyB:
        case constants::inputSignal::keyC:
        case constants::inputSignal::keyD:
        case constants::inputSignal::keyE:
            myState = state::selection;
            break;
        case constants::inputSignal::nop:
            break;
    }
}

void menue::itemSelectionMenue(constants::inputSignal aSignal) {
    char myFirstLine[17] = {""}, mySecondLine[17] = {""};
    strcat(mySecondLine, constants::lcdContent::lables[0]);
    switch(aSignal){
        case constants::inputSignal::keyA:
            myEntryId++;
            myEntryId %= 12;
            makeCombinedLine(myFirstLine,constants::lcdContent::names[myEntryId],constants::lcdContent::menue[0]);
            //myLcd.cursor()
            break; 
        case constants::inputSignal::keyB: 
            if (myEntryId == 0){
                myEntryId = 11;
            } else {
                myEntryId--;
            }
            makeCombinedLine(myFirstLine,constants::lcdContent::names[myEntryId],constants::lcdContent::menue[0]);
            break;
        case constants::inputSignal::keyC: 
            // not used in this menue
            break;
        case constants::inputSignal::keyD: 
            myEntryDefined = true;
            myPosSelected = false;
            myPos = 0;
            if (myEntryId < configTablePageCount) {
                getConfigTblPage(myEntryId, mySet);
            } else if (myEntryId == 8) {
                getManDelay(mySingleValue);
            } else if (myEntryId == 9){
                getContrast(mySingleValue);
            }
            break;
        case constants::inputSignal::keyE:
            myState = state::home;
            //homeScreen();
            break;
        default:
            break;
    }  
}

void menue::parameterSelectionMenue(constants::inputSignal aSignal) {

}

void menue::statusMenue(constants::inputSignal aSignal) {

}

void menue::durationMenue(constants::inputSignal aSignal) {

}

void menue::startMenue(constants::inputSignal aSignal) {

}

void menue::endMenue(constants::inputSignal aSignal) {

}

void menue::dayMenue(constants::inputSignal aSignal) {

}

void menue::matrixMenue(constants::inputSignal aSignal) {

}

void menue::timeMenue(constants::inputSignal aSignal) {

}

void menue::dateMenue(constants::inputSignal aSignal) {

}

void menue::contrastMenue(constants::inputSignal aSignal) {

}