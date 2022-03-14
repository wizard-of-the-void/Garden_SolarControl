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