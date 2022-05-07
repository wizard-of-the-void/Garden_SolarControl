//                                0123456789ABCDEF 
#include "menue.h"

menue::menue(relaisInterface *aRelaisInterface, RTC_DS3231 *aRTC):myLcd(constants::lcd_rs, constants::lcd_en, 
                        constants::lcd_d4, constants::lcd_d5, 
                        constants::lcd_d6, constants::lcd_d7) {
    theRelaisInterface = aRelaisInterface;
    theRTC = aRTC;
    myLcd.begin(16, 2);
}

void menue::changeState(bool aMenueState) {
    if (aMenueState) {
        myLcd.clear();
        myLcd.display();
        myPos = 0;
        myEntryId = 0;
        myPosSelected = false;
        myEntryDefined = false;
        homeScreen();
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
    if (!myEntryDefined) {
        itemSelectionMenue(aSignal);
    } else if (!myPosSelected) {
        switch (myEntryId) {
            case 0:
            case 1:
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
            case 7:
                parameterSelectionMenue(aSignal);
                break;
            case 8:
                break;
            case 9:
                contrastMenue(aSignal);
                break;
            case 10:
                timeMenue(aSignal);
                break;
            case 11:
                dateMenue(aSignal);
                break;
        } 
    } else {
        switch (myPos)
        {
        case 0:
            statusMenue(aSignal);
            break;
        case 1:
            durationMenue(aSignal);
            break;
        case 2:
            startMenue(aSignal);
            break;
        case 3:
            endMenue(aSignal);
            break;
        case 4:
            dayMenue(aSignal);
            break;
        case 5:
            matrixMenue(aSignal);
            break;
        default:
            homeScreen();
            break;
        }
    }
}


void menue::update(void) {

}


void menue::homeScreen(void) {

}

void menue::itemSelectionMenue(constants::inputSignal aSignal) {
    char myFirstLine[17] = {""}, mySecondLine[17] = {""};
    strcat(mySecondLine, constants::lcdContent::lables[0]);
    switch(aSignal){
        case constants::inputSignal::keyA:
            myEntryId++;
            myEntryId %= 12;
            memset(myFirstLine, 0, 17);
            strcat(myFirstLine, constants::lcdContent::names[myEntryId]);
            strcat(myFirstLine, constants::lcdContent::menue[0]);
            //myLcd.cursor()
            break; 
        case constants::inputSignal::keyB: 
            if (myEntryId == 0){
                myEntryId = 11;
            } else {
                myEntryId--;
            }
            memset(myFirstLine, 0, 17);
            strcat(myFirstLine, constants::lcdContent::names[myEntryId]);
            strcat(myFirstLine, constants::lcdContent::menue[0]);
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
            homeScreen();
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