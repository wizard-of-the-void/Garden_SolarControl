#ifndef _STORAGE_H_
#define _STORAGE_H_

#include <Arduino.h>
#include <EEPROM.h>

struct simpleTime {
    uint8_t hour;
    uint8_t minute;
};

struct parameterSet {
bool state;
simpleTime start, end;
uint8_t routingBitmap;
uint8_t daysOfWeek;
uint8_t delay;
};

const constexpr uint8_t configTablePageSize = sizeof(parameterSet);
const constexpr uint8_t configTablePageCount = 8;

void setConfigTblPage(uint8_t aPage, parameterSet &aParameterSet);
void getConfigTblPage(uint8_t aPage, parameterSet &aParameterSet);

void setManDelay(uint8_t aDelay);
void getManDelay(uint8_t &aDelay);

void setContrast(uint8_t aValue);
void getContrast(uint8_t &aValue);

void resetConfigData(void);
#endif