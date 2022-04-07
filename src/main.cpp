#include <inttypes.h>
#include <Arduino.h>
#include <RTClib.h>
#include <Adafruit_MCP23X17.h>

#include "constants.h"
#include "isr.h"
#include "relais.h"
#include "menue.h"

RTC_DS3231 rtc;
Adafruit_MCP23X17 mcp;
uint8_t ioMatrix[2];
//volatile signal_names signal;
relaisInterface relais(constants::relay_count, constants::relay_out);
//menue myMenue;
enum class inputSignal:uint8_t {nop, timerA, timerB, sensorA, sensorB, switchA, switchB, switchC, switchD, doorSwitch, keyA, keyB, keyC, keyD};
inputSignal signalBuffer[constants::signalBufferSize];
uint8_t recordIndex = 0, readIndex = 0;

LiquidCrystal myLcd = LiquidCrystal(constants::lcd_rs, constants::lcd_en, constants::lcd_d4, constants::lcd_d5, constants::lcd_d6, constants::lcd_d7);
LiquidCrystal* screen::myLcd = myLcd;
testObj myTest;
namespace myScreens {
    mainScreen myMainScreen;
    selectionScreen mySelectionScreens[12] = {
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeSelection]), 
        selectionScreen(constants::lcdContent::str[constants::lcdContent::matrixSelection]), 
        selectionScreen(constants::lcdContent::str[constants::lcdContent::clockSelection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::dateSelection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::contrastSelection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeManSelection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeBw1Selection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeBw2Selection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeZ1Selection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeZ2Selection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeT1Selection]),
        selectionScreen(constants::lcdContent::str[constants::lcdContent::timeT2Selection])
        };
    durationScreen myDurationScreens[5] = {
        durationScreen(constants::lcdContent::str[constants::lcdContent::durationsMax], &myTest ),
        durationScreen(constants::lcdContent::str[constants::lcdContent::durationsBw1], &myTest ),
        durationScreen(constants::lcdContent::str[constants::lcdContent::durationsBw2], &myTest ),
        durationScreen(constants::lcdContent::str[constants::lcdContent::durationTs1], &myTest ),
        durationScreen(constants::lcdContent::str[constants::lcdContent::durationTs2], &myTest )
    };

    timeScreen myTimeScreens[9] = {
        timeScreen(constants::lcdContent::str[constants::lcdContent::Bw1StrTime], &myTest),
        timeScreen(constants::lcdContent::str[constants::lcdContent::Bw1EndTime], &myTest),
        timeScreen(constants::lcdContent::str[constants::lcdContent::Bw2StrTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::Bw2EndTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::z1StrTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::z1EndTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::z2StrTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::z2EndTime], &myTest ),
        timeScreen(constants::lcdContent::str[constants::lcdContent::timeAdjust], &myTest )
    };

    stateScreen myStateScreens[2] =  {
        stateScreen(constants::lcdContent::str[constants::lcdContent::z1State], &myTest ),
        stateScreen(constants::lcdContent::str[constants::lcdContent::z2State], &myTest )
    };

    multiStateScreen myMultiStateScreens[14] = {
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z1WkDays] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z2WkDays] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::bw1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::bw2Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::ts1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::ts2Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z2Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::bw1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::bw2Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::ts1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::ts2Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z1Matrix] , &myTest ),
        multiStateScreen(constants::lcdContent::str[constants::lcdContent::z2Matrix] , &myTest )        
    };

    dateScreen myDateScreen = dateScreen(constants::lcdContent::str[constants::lcdContent::dateAdjust], &myTest );
    barScreen myContrastScreen = barScreen(constants::lcdContent::str[constants::lcdContent::contrastAdjust], &myTest );    

    //Linking the Screens:
}

void setLinks(void) {
  using namespace myScreens;
  myMainScreen.setLinks(nullptr, nullptr,nullptr, &mySelectionScreens[0]);
  //Main selectionMenu
  mySelectionScreens[0].setLinks(&myMainScreen, &mySelectionScreens[4], &mySelectionScreens[1], &mySelectionScreens[5]);
  mySelectionScreens[1].setLinks(&myMainScreen, &mySelectionScreens[0], &mySelectionScreens[2], &myMultiStateScreens[2]);
  mySelectionScreens[2].setLinks(&myMainScreen, &mySelectionScreens[1], &mySelectionScreens[3], &myTimeScreens[8]);
  mySelectionScreens[3].setLinks(&myMainScreen, &mySelectionScreens[2], &mySelectionScreens[4], &myDateScreen);
  mySelectionScreens[4].setLinks(&myMainScreen, &mySelectionScreens[3], &mySelectionScreens[0], &myContrastScreen);
  //Duration subSelectionMenu
  mySelectionScreens[5].setLinks(&mySelectionScreens[0], &mySelectionScreens[9], &mySelectionScreens[6], &myDurationScreens[0]);
  mySelectionScreens[6].setLinks(&mySelectionScreens[0], &mySelectionScreens[5], &mySelectionScreens[7], &myTimeScreens[0]);
  mySelectionScreens[7].setLinks(&mySelectionScreens[0], &mySelectionScreens[6], &mySelectionScreens[8], &myTimeScreens[2]);
  mySelectionScreens[8].setLinks(&mySelectionScreens[0], &mySelectionScreens[7], &mySelectionScreens[9], &myStateScreens[0]);
  mySelectionScreens[9].setLinks(&mySelectionScreens[0], &mySelectionScreens[8], &mySelectionScreens[5], &myStateScreens[1]);
  //Man Durations
  myDurationScreens[0].setLinks(&mySelectionScreens[5],&myDurationScreens[4],&myDurationScreens[3], nullptr);
  myDurationScreens[3].setLinks(&mySelectionScreens[5],&myDurationScreens[0],&myDurationScreens[4], nullptr);
  myDurationScreens[4].setLinks(&mySelectionScreens[5],&myDurationScreens[3],&myDurationScreens[0], nullptr);
  //Bw1

  //Bw2

  //Z1

  //Z2

  //Ts1

  //Ts2

}

menue myMenue = menue(&myScreens::myMainScreen);

void setup() {
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
