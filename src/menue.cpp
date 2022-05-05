//                                0123456789ABCDEF 
#include "menue.h"

menue::menue() {

}

void menue::changeState(bool aMenueState) {
    if (aMenueState) {
        myLcd.clear();
        myLcd.display();
        myPos = 0;
        myEntryId = 0;
        myPosSelected = false;
        myEntryDefined = false;
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
    char myFirstLine[17] = {""}, mySecondLine[17] = {""};
    if (!myEntryDefined) {
        strcat(mySecondLine, constants::lcdContent::lables[0]);
        switch(aSignal){
            case constants::inputSignal::keyA:
                myEntryId++;
                myEntryId %= 12;
                memset(myFirstLine, 0, 17);
                strcat(myFirstLine, constants::lcdContent::names[myEntryId]);
                strcat(myFirstLine, constants::lcdContent::menue[0]);
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
                myPos = 0;
                break;
            case constants::inputSignal::keyE:
                break;
            default:
                break;
        }        
    } else {
        switch(myPos) {
            case 0:
            case 1:
                break;

        }
    }
}

void menue::update(void) {

}