#ifndef _CONSTANTS_H_
#define _CONSTANTS_H_
#include <inttypes.h> 
#include <avr/pgmspace.h>

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
                            
                            timerCount = 2,
                            timerPageOffset = 0,

                            mainRingBufferSize  = 32,
                            isrRingBufferSize   = 16,
                            
                            loopLimit = 128,

                            screenCount      = 32;

enum class inputSignal:uint8_t {nop=255, timerIrq=254,
                                timerA=0, timerB=1, 
                                sensorA=2, sensorB=3, 
                                switchA=4, switchB=5, switchC=6, switchD=7, 
                                doorSwitch=250, alert=251, 
                                keyA=128, keyB=129, keyC=130, keyD=131, keyE=132};

enum class timerState:uint8_t {timerA_armed, timerB_armed, timer_unarmed};

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

const char str_name_01[] PROGMEM = { "Zschlt01" },
                    str_name_02[] = { "Zschlt02" },
                    str_name_03[] = { "Melder01" },
                    str_name_04[] = { "Melder02" },
                    str_name_05[] = { "Taster-1" },
                    str_name_06[] = { "Taster-2" },
                    str_name_07[] = { "Taster-3" },
                    str_name_08[] = { "Taster-4" },
                    str_name_09[] = { "WechselZ" },
                    str_name_10[] = { "Kontrast" },                    
                    str_name_11[] = { "Uhrzeit " },
                    str_name_12[] = { "Datum   " },

                    str_short_01[] = { "ZS-1" },
                    str_short_02[] = { "ZS-2" },
                    str_short_03[] = { "BM-1" },
                    str_short_04[] = { "BM-2" },
                    str_short_05[] = { "TS-1" },
                    str_short_06[] = { "TS-2" },
                    str_short_07[] = { "TS-3" },
                    str_short_08[] = { "TS-4" },
                    
                    str_menue_00[] = { " ändern?" },
                    str_menue_01[] = { "-Status: EIN" }, //=> StateScreen 2
                    str_menue_02[] = { "-Ein: ###min" }, //=> DurationScreen 2
                    str_menue_03[] = { "-Str-Z:##:##" }, //=> TimeScreen 2
                    str_menue_04[] = { "-End-Z:##:##" }, //=> TimeScreen 2
                    str_menue_05[] = { "-WTg:1234567" }, //=> DayScreen 2
                    str_menue_06[] = { " => 12345678" }, //=> MatrixScreen 2
                    str_menue_07[] = { "Zeit:      00:00" }, //=> TimeScreen 2
                    str_menue_08[] = { "Datum DD.MM.YYYY" }, //=> DateScreen 2                            
                    str_menue_09[] = { "0------|-------9" }, //=> BarScreen 2

                    str_label_01[] = { "W  Z  #  E, => M" }, //=> SeclectionScreen
                    str_label_02[] = { "W  Z  A  E  => M" }, //=> DayScreen
                    str_label_03[] = { "W  Z  +  -  => M" }, //=> DurationScreen, TimeScreen, DateScreen
                    str_label_04[] = { "#  #  +  -  => M" }; //=> BarScreen, StateScreen            

    const char *const names[] PROGMEM = { str_name_01, str_name_02, str_name_03,
                                        str_name_04, str_name_05, str_name_06,
                                        str_name_07, str_name_08, str_name_09,
                                        str_name_10, str_name_11, str_name_12 }; 

    const char *const shorts[] PROGMEM = { str_short_01, str_short_02, str_short_03,
                                        str_short_04, str_short_05, str_short_06,
                                        str_short_07, str_short_08 }; 

    const char *const menue[] PROGMEM = { str_menue_01, str_menue_02, str_menue_03,
                                        str_menue_04, str_menue_05, str_menue_06,
                                        str_menue_07, str_menue_08, str_menue_09 }; 

    const char *const lables[] PROGMEM = { str_label_01, str_label_02, str_label_03,
                                        str_label_04 };

    }
}
#endif