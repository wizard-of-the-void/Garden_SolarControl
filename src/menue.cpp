#include "menue.h"

menue::menue(screen* aInitScreen) : myLcd(constants::lcd_rs, constants::lcd_en, constants::lcd_d4, constants::lcd_d5, constants::lcd_d6, constants::lcd_d7) {
    myActiveScreen = aInitScreen;
}

void menue::displayOn(void) {
  //Background on
  analogWrite(constants::lcd_backlight, constants::lcd_brightness);
  //Power up
  myLcd.display();
}

void menue::displayOff(void) {
  //Background off
  analogWrite(constants::lcd_backlight, 0);
  //Power down  
  myLcd.noDisplay();
}

void menue::reactToSignal(uint8_t aSignal) {
    if (myActiveScreen != nullptr) {
        myActiveScreen = myActiveScreen->receiveSignal(aSignal);
    }
}

screen::screen(LiquidCrystal *aLcd, const char* aFirstLine, const char* aSecondLine) {
    myLcd = aLcd;
    myFirstLine = aFirstLine;
    mySecondLine = aSecondLine;
}

screen::screen(const char* aFirstLine, const char* aSecondLine) {
    myFirstLine = aFirstLine;
    mySecondLine = aSecondLine;
}

void screen::setLinks(screen *parentScreen, screen *pervScreen, screen *nextScreen, screen *childScreen) {
    myParentScreen = parentScreen;
    myPervScreen = pervScreen;
    myNextScreen = nextScreen;
    myChildScreen = childScreen;
}

screen* screen::getScreen(screenRelation aRelation) {
    switch (aRelation)
    {
    case screenRelation::parent :
        if (myParentScreen == nullptr) {
            return this;
        } else {
            return myParentScreen;
        }
        break;
    case screenRelation::child :
        if (myChildScreen == nullptr) {
            return this;
        } else {
            return myChildScreen;
        }
        break;
    case screenRelation::previous :
        if (myPervScreen == nullptr) {
            return this;
        } else {
            return myPervScreen;
        }
        break;
    case screenRelation::next :
        if (myNextScreen == nullptr) {
            return this;
        } else {
            return myNextScreen;
        }
        break;
    default:
        return this;
        break;
    }
}

void screen::initText(bool showCursor) {
    this->myLcd->clear();
    this->myLcd->setCursor(0,0);

    char buffer[17];
    strcpy_P(buffer, (char *)pgm_read_word(&(myFirstLine)));
    this->myLcd->print(buffer);
    this->myLcd->setCursor(1,0);

    strcpy_P(buffer, (char *)pgm_read_word(&(mySecondLine)));
    this->myLcd->print(buffer);
    if (showCursor) {
        this->myLcd->cursor();
    } else {
        this->myLcd->noCursor();
    }
}
    
void screen::updateChar(uint8_t aPos, char aChar) {
    this->myLcd->setCursor(0,aPos);
    this->myLcd->print(aChar);
}
    
void screen::updateLine(char aLine[17]) {
    this->myLcd->setCursor(0,0);
    this->myLcd->print(aLine);
}

void screen::setCursor(uint8_t aPos) {
    this->myLcd->setCursor(0,aPos);
}
        
void screen::activate(void) {

}


mainScreen::mainScreen():screen(constants::lcdContent::str[constants::lcdContent::Empty], 
                                constants::lcdContent::str[constants::lcdContent::Empty]){
    
} 

screen* mainScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

selectionScreen::selectionScreen(const char* firstLine) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine1]) //, firstLine, selectionScreen::secondLine) {
    {
}

screen* selectionScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

durationScreen::durationScreen(const char* firstLine, durationObj* aDurationObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine3]) {}
screen* durationScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

timeScreen::timeScreen(const char* firstLine, timeObj* aTimeObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine3]) {}
screen* timeScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

stateScreen::stateScreen(const char* firstLine, multiStateObj* aStateObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine4]) {}
screen* stateScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

multiStateScreen::multiStateScreen(const char* firstLine, multiStateObj* aMultiStateObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine2]) {}
screen* multiStateScreen::receiveSignal(uint8_t aSignal) {
    return this;
}

dateScreen::dateScreen(const char* firstLine, timeObj* aTimeObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine3]) {}
screen* dateScreen::receiveSignal(uint8_t aSignal){
    return this;
}

barScreen::barScreen(const char* firstLine, valueObj* aValueObj) : screen(firstLine, constants::lcdContent::str[constants::lcdContent::sndLine4]) {}
screen* barScreen::receiveSignal(uint8_t aSignal) {
    return this;
}


void testObj::setDuration(uint8_t aIdx, uint8_t aDuration) {}
void testObj::setDateTime(uint8_t aIdx, DateTime aDateTime) {}
void testObj::setState(uint8_t aIdx, bool aState) {}
void testObj::setValue(uint8_t aValue) {}

uint8_t testObj::getDuration(uint8_t aIdx){
    return 42;
}

DateTime testObj::getDateTime(uint8_t aIdx) {
    return DateTime("2022-03-14T22:00:00");
}

bool testObj::getState(uint8_t aIdx) {
    return true;
}

uint8_t testObj::getValue(void) {
    return 42;
}

uint8_t testObj::stateCount(void) {
    return 42;
}