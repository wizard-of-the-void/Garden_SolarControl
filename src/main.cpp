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
relaisInterface theRelais(constants::relay_count, constants::relay_out, &theRtc);

// setup input ring buffer
constants::inputSignal theSignalBuffer[constants::signalBufferSize] = {constants::inputSignal::nop};
uint8_t theRecordIndex = 0, theReadIndex = 0;
constants::timerState activeTimer = constants::timerState::timer_unarmed;

// setup the menue
bool theMenueState = false;
menue theMenue;

void updateTimerAlert(void) {
  parameterSet timerLst[2];
  getConfigTblPage(uint8_t (constants::inputSignal::timerA),timerLst[0]);
  getConfigTblPage(uint8_t (constants::inputSignal::timerB),timerLst[1]);

  DateTime myNow = theRtc.now();
  DateTime myNextAlert = myNow + TimeSpan(1,0,0,0);
  uint8_t myOffset = (myNow.dayOfTheWeek() + 6) % 7;
  activeTimer = constants::timerState::timer_unarmed;
  for (uint8_t i = 0; i < 2; i++) {
    if (timerLst[i].state) {
      for (uint8_t j = 0; j < 7; j++) {
        if (timerLst[i].daysOfWeek & (0b00000001 << ((myOffset + j)%7))) {
          if(myNextAlert > (DateTime(myNow.year(), myNow.month(),myNow.day(), timerLst[i].start.hour, timerLst[i].start.minute,0) + TimeSpan(j,0,0,0))) {
            myNextAlert = DateTime(myNow.year(), myNow.month(),myNow.day(), timerLst[i].start.hour, timerLst[i].start.minute,0) + TimeSpan(j,0,0,0);
          }
          break;
        }
      }
    }
  }
}

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
  if (theRecordIndex != theReadIndex) {
    constants::inputSignal mySignal;
    theReadIndex++;
    theReadIndex %= constants::signalBufferSize;

    mySignal = theSignalBuffer[theReadIndex];
    theSignalBuffer[theReadIndex] = constants::inputSignal::nop;
  
    if (mySignal == constants::inputSignal::timerIrq) {
      switch (activeTimer) {
        case constants::timerState::timerA_armed:
          mySignal = constants::inputSignal::timerA;
        case constants::timerState::timerB_armed:
          mySignal = constants::inputSignal::timerB;
        default:
          mySignal = constants::inputSignal::nop;
      }
      updateTimerAlert();
    }
    switch (mySignal) {
      case constants::inputSignal::timerA: 
      case constants::inputSignal::timerB:
      case constants::inputSignal::sensorA:
      case constants::inputSignal::sensorB: 
      case constants::inputSignal::switchA: 
      case constants::inputSignal::switchB: 
      case constants::inputSignal::switchC:
      case constants::inputSignal::switchD:
        parameterSet mySet;
        getConfigTblPage(uint8_t(mySignal), mySet);
        theRelais.processParameterSet(mySet);
        theMenue.update();
        break;
      case constants::inputSignal::keyA: 
      case constants::inputSignal::keyB: 
      case constants::inputSignal::keyC: 
      case constants::inputSignal::keyD: 
      case constants::inputSignal::keyE:
        theMenue.processSignal(mySignal);
        break;
      case constants::inputSignal::doorSwitch: 
        theMenue.changeState(theMenueState);
        theMenue.update();
        break;
      case constants::inputSignal::alert:
        theRelais.processAlert();
        theMenue.update();
      case constants::inputSignal::nop:
        break;
    }
  } else {
    //go to sleep after 3 waits.
  }
}
