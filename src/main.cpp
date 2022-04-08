#include <inttypes.h>
#include <Arduino.h>
#include <RTClib.h>
#include <Adafruit_MCP23X17.h>

#include "constants.h"
#include "isr.h"
#include "relais.h"
#include "menue.h"
#include "storage.h"

// setup external components
RTC_DS3231 theRtc;
Adafruit_MCP23X17 theMcp;
LiquidCrystal theLcd = LiquidCrystal(constants::lcd_rs, constants::lcd_en, 
                                      constants::lcd_d4, constants::lcd_d5, 
                                      constants::lcd_d6, constants::lcd_d7);
relaisInterface theRelais(constants::relay_count, constants::relay_out);

// setup input ring buffer
enum class inputSignal:uint8_t {nop, 
                                timerA, timerB, 
                                sensorA, sensorB, 
                                switchA, switchB, switchC, switchD, 
                                doorSwitch, 
                                keyA, keyB, keyC, keyD, keyE};
inputSignal theSignalBuffer[constants::signalBufferSize] = {inputSignal::nop};
uint8_t theRecordIndex = 0, theReadIndex = 0;

void setup() {
  parameterSet mySet;
  getConfigTblPage(configTablePageCount-1, mySet);
  if (mySet.daysOfWeek && 0x80) resetConfigData();
  /*
  // put your setup code here, to run once:
  Serial.begin(9600);

  // clear the buffer to make sure we have a know state
  for (uint8_t i = 0; i < constants::signalBufferSize; i++ ){
    signalBuffer[i] = inputSignal::nop;
  }
  // initializing the rtc
  if(!rtc.begin()) {
      Serial.println("Couldn't find RTC!");
      Serial.flush();
      abort();
  }

  if(rtc.lostPower()) {
      // this will adjust to the date and time at compilation
      rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
  //we don't need the 32K Pin, so disable it
  rtc.disable32K();
  
  // Making it so, that the alarm will trigger an interrupt
  pinMode(constants::irq_A, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(constants::irq_A), onTimer, FALLING);
  
  // set alarm 1, 2 flag to false (so alarm 1, 2 didn't happen so far)
  // if not done, this easily leads to problems, as both register aren't reset on reboot/recompile
  rtc.clearAlarm(1);
  rtc.clearAlarm(2);
  
  // stop oscillating signals at SQW Pin
  // otherwise setAlarm1 will fail
  rtc.writeSqwPinMode(DS3231_OFF);
  
  // turn off alarm 2 (in case it isn't off already)
  // again, this isn't done at reboot, so a previously set alarm could easily go overlooked
  rtc.disableAlarm(1);
  rtc.disableAlarm(2);
  
  // schedule an alarm 10 seconds in the future
  if(!rtc.setAlarm1(
          rtc.now() + TimeSpan(10),
          DS3231_A1_Second // this mode triggers the alarm when the seconds match. See Doxygen for other options
  )) {
      Serial.println("Error, alarm wasn't set!");
  }else {
      Serial.println("Alarm will happen in 10 seconds!");  
  } 
  */ 
}

void loop() {
 /* switch (signal) {
    case PIR01: 
    case PIR02: 
    case KEY01: 
    case KEY02: 
      routeSignal(signal);
      break;
    case C_BTN: 
      //displayOn();
      break;
    case BTN01:
      if (menu) {

      } else {
        relais.directToggle(0);
      }
      break;
    case BTN02:
      if (menu) {

      } else {
        relais.directToggle(1);
      }
      break;    
    case BTN03:
      if (menu) {

      } else {
        relais.directToggle(2);
      }
      break;    
    case BTN04:
      if (menu) {

      } else {
        relais.directToggle(3);
      }
      break;    
    case BTN05: 
      break;         
  } */
}
