#include <inttypes.h>
#include <Arduino.h>
#include <avr/sleep.h>
#include <RTClib.h>
#include <Adafruit_MCP23X17.h>

#include "constants.h"
#include "ringbuffers.h"
#include "timerInterface.h"
#include "isr.h"
#include "relais.h"
#include "menue.h"
#include "storage.h"

// setup external components
RTC_DS3231 theRtc = RTC_DS3231();
Adafruit_MCP23X17 theMcp = Adafruit_MCP23X17();
/*LiquidCrystal theLcd = LiquidCrystal(constants::lcd_rs, constants::lcd_en, 
                                      constants::lcd_d4, constants::lcd_d5, 
                                      constants::lcd_d6, constants::lcd_d7); */
relaisInterface theRelais = relaisInterface(constants::relay_count, constants::relay_out, &theRtc);
timerInterface theTimerInterface = timerInterface(&theRtc);

uint8_t loopCount = 0;

// setup the menue
menue theMenue = menue(&theRelais, &theRtc);

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
  transfereIsrToMainRing(&theTimerInterface);
  if (mainRing::level > 0) {
    constants::inputSignal mySignal;
    mySignal = mainRing::read();

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
        loopCount = 0;
        //theMenue.update();
        break;
      case constants::inputSignal::keyA: 
      case constants::inputSignal::keyB: 
      case constants::inputSignal::keyC: 
      case constants::inputSignal::keyD: 
      case constants::inputSignal::keyE:
        //theMenue.processSignal(mySignal);
        loopCount = 0;
        break;
      case constants::inputSignal::doorSwitch: 
        //theMenue.changeState(theMenueState);
        //theMenue.update();
        loopCount = 0;
        break;
      case constants::inputSignal::alert:
        theRelais.processAlert();
        //theMenue.update();
        loopCount = 0;
      case constants::inputSignal::nop:
        loopCount++;
      default:
        break;
    }
  } else {
    //go to sleep after loopLimit nop instructions.
    if (loopCount >= constants::loopLimit) {
      set_sleep_mode(SLEEP_MODE_PWR_DOWN);
      sleep_enable();
      sleep_mode();
      sleep_disable();
      loopCount = 0;
    }
  }
}
