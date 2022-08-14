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

void menue::clearLineBuffer() {
    memset(myLines, 0, sizeof(myLines[0][0]) * (constants::lcd_conf_rows) * (constants::lcd_conf_cols + 1));
}

void menue::makeFirstLine(state aState) {

}

void menue::makeSecondLine(state aState) {
    snprintf(myLines[1], constants::lcd_conf_cols + 1, constants::lcdContent::lables[static_cast<uint8_t>(aState)]);
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

    //Update first lines content
    myLcd.setCursor(0,0);
    myLcd.println(myLines[0]);
    
    //If screen changed update second lines content
    if (myOldState != myState){
        makeSecondLine(myState);
        myLcd.println(myLines[1]);
        myOldState = myState;
    }
}

void menue::homeScreen(constants::inputSignal aSignal) {
    DateTime myTimteStamp = theRTC->now();
    snprintf(myLines[0], constants::lcd_conf_cols+1, constants::lcdContent::menue[0], 
        myTimteStamp.day(), myTimteStamp.month(), myTimteStamp.year(), 
        myTimteStamp.hour(), myTimteStamp.minute());
    if (myOldState != state::home){
        snprintf(myLines[1], constants::lcd_conf_cols+1, constants::lcdContent::lables[0]);
    }
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
    switch(aSignal){
        case constants::inputSignal::keyA:
            myEntryId++;
            myEntryId %= 12;
            snprintf(myLines[0], 
                    constants::lcd_conf_cols+1, 
                    constants::lcdContent::menue[1], 
                    constants::lcdContent::names[myEntryId]);
            break; 
        case constants::inputSignal::keyB: 
            if (myEntryId == 0){
                myEntryId = 11;
            } else {
                myEntryId--;
            }
            snprintf(myLines[0], 
                    constants::lcd_conf_cols+1, 
                    constants::lcdContent::menue[1], 
                    constants::lcdContent::names[myEntryId]);
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

void menue::setContrast(uint8_t aContrast) {

}