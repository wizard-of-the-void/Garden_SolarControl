#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <inttypes.h> 

namespace constants {
 constexpr uint8_t //Hardware settings
                        //------------------------
                        //  LCD-Io-Pins
                            lcd_rs          =  9,
                            lcd_en          =  8, 
                            lcd_d4          =  7, 
                            lcd_d5          =  6, 
                            lcd_d6          =  4, 
                            lcd_d7          =  1,
                        //------------------------
                        //  LCD-Power-Pins
                        //  lcd_power       = 0,
                            lcd_backlight   =  5,
                        //------------------------
                        //  LCD-Configuration
                            lcd_conf_rows   = 2,
                            lcd_conf_cols   = 16,
                            lcd_brightness  = 255,
                        //------------------------
                        //  Case-Switch-Pin (MCP)
                            case_sw_in      = 0,
                        //------------------------
                        //  Case-Button-Pins (MCP)
                            case_btn_in[5]  = {1, 2, 3, 4, 5},
                        //------------------------
                        //  Output Pins (328)
                            relay_out[4]    = {10, 11, 12, 13},
                            relay_count     = 4,
                        //------------------------
                        //  I2C-Addresses
                            i2c_addr_mcp    = 0,
                            i2c_addr_rtc    = 0,
                            i2c_addr_eeprom = 0,
                        //------------------------
                        //  Ext-Input-Pins (MCP)
                            ext_in[8]       = {8, 9, 10, 11, 12, 13, 14, 15},
                        //------------------------
                        //  Interrupt Pins
                            irq_A           = 3,
                            irq_B           = 2,
                            
                            signalBufferSize = 32,
                            
                            screenCount      = 32;

enum class inputSignal:uint8_t {nop=255, timerIrq=254,
                                timerA=0, timerB=1, 
                                sensorA=2, sensorB=3, 
                                switchA=4, switchB=5, switchC=6, switchD=7, 
                                doorSwitch=250, alert=251, 
                                keyA=128, keyB=129, keyC=130, keyD=131, keyE=132};

enum class timerState:uint8_t {timerA_armed, timerB_armed, timer_unarmed};
enum signalSource {PIR01 = 0, PIR02 = 1, KEY01 = 2, KEY02 = 3, C_BTN, BTN01, BTN02, BTN03, BTN04, BTN05};

    namespace lcdContent {
        enum signalSource {
            Empty = 0, 
            timeSelection = 1, 
            matrixSelection = 2, 
            clockSelection = 3, 
            dateSelection = 4, 
            contrastSelection = 5,
            
            durationsMax = 6, 
            durationsBw1 = 7, 
            durationsBw2 = 8,
            
            Bw1StrTime = 9,
            Bw1EndTime = 10,

            Bw2StrTime = 11,
            Bw2EndTime = 12,

            durationTs1 = 13,
            durationTs2 = 14,

            z1State = 15,
            z1StrTime = 16,
            z1EndTime = 17,
            z1WkDays = 18,

            z2State = 19,
            z2StrTime = 20,
            z2EndTime = 21,
            z2WkDays = 22,

            bw1Matrix = 23,
            bw2Matrix = 24,
            ts1Matrix = 25,
            ts2Matrix = 26,
            z1Matrix = 27,
            z2Matrix = 28,
            
            timeAdjust = 29,
            dateAdjust = 30,
            contrastAdjust = 31,
            
            sndLine1 = 32,
            sndLine2 = 33,
            sndLine3 = 34,
            sndLine4 = 35,
            sndLine5 = 36,
            
            timeManSelection = 37,
            timeBw1Selection = 38,
            timeBw2Selection = 39,
            timeZ1Selection  = 40,
            timeZ2Selection  = 41,
            timeT1Selection  = 42,
            timeT2Selection  = 43 };
//       0123456789ABCDEF 
const char PROGMEM  str_01[] = { "                " }, //=> MainScreen
                    str_02[] = { "Zschltg aendern?" }, //=> SeclectionScreen 2
                    str_02_01[] = { "Manuel   ändern?" },
                    str_02_02[] = { "Melder-1 ändern?" },
                    str_02_03[] = { "Melder-2 ändern?" },
                    str_02_04[] = { "Zeit-1   ändern?" },
                    str_02_05[] = { "Zeit-2   ändern?" },
                    str_02_06[] = { "Taster-1 ändern?" },
                    str_02_07[] = { "Taster-2 ändern?" },                                        
                    str_03[] = { "Matrix  aendern?" }, //=> SeclectionScreen 2
                    str_04[] = { "Uhrzeit aendern?" }, //=> SeclectionScreen 2
                    str_05[] = { "Datum   aendern?" }, //=> SeclectionScreen 2
                    str_06[] = { "Kontrst aendern?" }, //=> SeclectionScreen 2

                    str_07[] = { "Man-Ein: ### Min" }, //=> DurationScreen 2
                    str_08[] = { "Bw1-Ein: ### Min" }, //=> DurationScreen 2
                    str_09[] = { "Bw2-Ein: ### Min" }, //=> DurationScreen 2

                    str_10[] = { "M-1-Str-Z: ##:##" }, //=> TimeScreen 2
                    str_11[] = { "M-1-End-Z: ##:##" }, //=> TimeScreen 2
                            
                    str_12[] = { "M-2-Str-Z: ##:##" }, //=> TimeScreen 2
                    str_13[] = { "M-2-End-Z: ##:##" }, //=> TimeScreen 2

                    str_14[] = { "T-1-Ein: ### Min" }, //=> DurationScreen 2
                    str_15[] = { "T-2-Ein: ### Min" }, //=> DurationScreen 2

                    str_16[] = { "Z1-Status:   EIN" }, //=> StateScreen 2
                    str_17[] = { "Z1-Str-Z:  ##:##" }, //=> TimeScreen 2
                    str_18[] = { "Z1-End-Z:  ##:##" }, //=> TimeScreen 2
                    str_19[] = { "Z1-WTage:1234567" }, //=> DayScreen 2
                            
                    str_20[] = { "Z2-Status:   EIN" }, //=> StateScreen 2
                    str_21[] = { "Z2-Str-Z:  ##:##" }, //=> TimeScreen 2
                    str_22[] = { "Z2-End-Z:  ##:##" }, //=> TimeScreen 2
                    str_23[] = { "Z2-WTage:1234567" }, //=> DayScreen 2

                    str_24[] = { "M-1 => A:1 2 3 4" }, //=> MatrixScreen 2
                    str_25[] = { "M-2 => A:1 2 3 4" }, //=> MatrixScreen 2
                    str_26[] = { "T-1 => A:1 2 3 4" }, //=> MatrixScreen 2
                    str_27[] = { "T-2 => A:1 2 3 4" }, //=> MatrixScreen 2
                    str_28[] = { "Z-1 => A:1 2 3 4" }, //=> MatrixScreen 2
                    str_29[] = { "Z-2 => A:1 2 3 4" }, //=> MatrixScreen 2

                    str_30[] = { "Zeit:      00:00" }, //=> TimeScreen 2

                    str_31[] = { "Datum DD.MM.YYYY" }, //=> DateScreen 2
                            
                    str_32[] = { "0------|-------9" }, //=> BarScreen 2

                    str_33[] = { "W  Z  #  E, => M" }, //=> SeclectionScreen
                    str_34[] = { "W  Z  A  E  => M" }, //=> DayScreen
                    str_35[] = { "W  Z  +  -  => M" }, //=> DurationScreen, TimeScreen, DateScreen
                    str_36[] = { "#  #  +  -  => M" }, //=> BarScreen, StateScreen            
                    str_37[] = { "1  2  3  4  => M" }; //=> MatrixScreen

    const char *const str[] PROGMEM = { str_01, str_02, str_03, str_04, str_05, str_06, str_07, str_08, str_09, str_10,
                                        str_21, str_22, str_23, str_24, str_25, str_26, str_27, str_28, str_29, str_30,
                                        str_31, str_32, str_33, str_34, str_35, str_36, str_37, 
                                        str_02_01, str_02_02, str_02_03, str_02_04, str_02_05, str_02_06, str_02_07 };
    }
}
/*
uint8_t     //  Online Configuration
            //------------------------
            //  Shut off delay
                pir_delay[2]    = {0, 0},
                switch_delay[2] = {0, 0},
            //------------------------
            // IO-Matrix
                ioMarix[2];
*/
#endif