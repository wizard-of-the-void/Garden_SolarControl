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
            sndLine5 = 36};
//       0123456789ABCDEF 
constexpr const char str[37][17] = {
        "                ", //=> MainScreen
        "Zschltg aendern?", //=> SeclectionScreen 2
        "Matrix  aendern?", //=> SeclectionScreen 2
        "Uhrzeit aendern?", //=> SeclectionScreen 2
        "Datum   aendern?", //=> SeclectionScreen 2
        "Kontrst aendern?", //=> SeclectionScreen 2

        "Max-Ein: ### Min", //=> DurationScreen 2
        "Bw1-Ein: ### Min", //=> DurationScreen 2
        "Bw2-Ein: ### Min", //=> DurationScreen 2

        "Bw1-Str-Z: ##:##", //=> TimeScreen 2
        "Bw1-End-Z: ##:##", //=> TimeScreen 2
        
        "Bw2-Str-Z: ##:##", //=> TimeScreen 2
        "Bw2-End-Z: ##:##", //=> TimeScreen 2

        "Ts1-Ein: ### Min", //=> DurationScreen 2
        "Ts2-Ein: ### Min", //=> DurationScreen 2

        "Z1-Status:   EIN", //=> StateScreen 2
        "Z1-Str-Z:  ##:##", //=> TimeScreen 2
        "Z1-End-Z:  ##:##", //=> TimeScreen 2
        "Z1-WTage:1234567", //=> DayScreen 2
        
        "Z2-Status:   EIN", //=> StateScreen 2
        "Z2-Str-Z:  ##:##", //=> TimeScreen 2
        "Z2-End-Z:  ##:##", //=> TimeScreen 2
        "Z2-WTage:1234567", //=> DayScreen 2

        "Bw1 => A:1 2 3 4", //=> MatrixScreen 2
        "Bw2 => A:1 2 3 4", //=> MatrixScreen 2
        "Ts1 => A:1 2 3 4", //=> MatrixScreen 2
        "Ts2 => A:1 2 3 4", //=> MatrixScreen 2
        "Z1  => A:1 2 3 4", //=> MatrixScreen 2
        "Z2  => A:1 2 3 4", //=> MatrixScreen 2

        "Zeit:      00:00", //=> TimeScreen 2

        "Datum DD.MM.YYYY", //=> DateScreen 2
        
        "0------|-------9", //=> BarScreen 2

        "W  Z  #  E, => M", //=> SeclectionScreen
        "W  Z  A  E  => M", //=> DayScreen
        "W  Z  +  -  => M", //=> DurationScreen, TimeScreen, DateScreen
        "#  #  +  -  => M", //=> BarScreen, StateScreen            
        "1  2  3  4  => M" //=> MatrixScreen
        };
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