#include "storage.h"

void setConfigTblPage(uint8_t aPage, parameterSet &aParameterSet) {
    EEPROM.put<parameterSet>(aPage * configTablePageSize, aParameterSet);
}

void getConfigTblPage(uint8_t aPage, parameterSet &aParameterSet) {
    EEPROM.get<parameterSet>(aPage * configTablePageSize, aParameterSet);
}

void setManDelay(uint8_t aDelay) {
    EEPROM.update(configTablePageCount * configTablePageSize, aDelay);
}

void getManDelay(uint8_t &aDelay) {
    aDelay = EEPROM.read(configTablePageCount * configTablePageSize);
}

void setContrast(uint8_t aValue) {
    EEPROM.update(configTablePageCount * configTablePageSize + 1, aValue);
}

void getContrast(uint8_t &aValue) {
    aValue = EEPROM.read(configTablePageCount * configTablePageSize + 1);
}

void resetConfigData(void) {
    parameterSet myTemplate;
    myTemplate.state            = true;
    myTemplate.start.hour       = 0xFF;
    myTemplate.start.minute     = 0xFF;
    myTemplate.end.hour         = 0xFF;
    myTemplate.end.minute       = 0xFF;
    myTemplate.routingBitmap    = 0b00000001;
    myTemplate.daysOfWeek       = 0b01111111;
    myTemplate.delay            = 1;
    for (uint8_t i = 0; i < configTablePageCount; i++) {
        setConfigTblPage(i, myTemplate);
        myTemplate.routingBitmap = myTemplate.routingBitmap << 1;
    }
    
    setManDelay(1);
    setContrast(0x80);
}