#ifndef DISPLAY_LCD_I2C_HAL_H
#define DISPLAY_LCD_I2C_HAL_H

#include <Print.h>

// commands
#define LCD_CLEARDISPLAY 0x01
#define LCD_RETURNHOME 0x02
#define LCD_ENTRYMODESET 0x04
#define LCD_DISPLAYCONTROL 0x08
#define LCD_CURSORSHIFT 0x10
#define LCD_FUNCTIONSET 0x20
#define LCD_SETCGRAMADDR 0x40
#define LCD_SETDDRAMADDR 0x80

// flags for display/cursor shift
#define LCD_DISPLAYMOVE 0x08
#define LCD_CURSORMOVE 0x00
#define LCD_MOVERIGHT 0x04
#define LCD_MOVELEFT 0x00

// hardware setup
#define LCD_DISPLAY_COLUMNS 16
#define LCD_DISPLAY_ROWS 2
#define LCD_DISPLAY_ADDRESS 0x27

// flags for function set
#define LCD_8BITMODE 0x10
#define LCD_4BITMODE 0x00
#define LCD_2LINE 0x08
#define LCD_1LINE 0x00
#define LCD_5x10DOTS 0x04
#define LCD_5x8DOTS 0x00

// flags for display on/off control
#define LCD_DISPLAYON 0x04
#define LCD_DISPLAYOFF 0x00
#define LCD_CURSORON 0x02
#define LCD_CURSOROFF 0x00
#define LCD_BLINKON 0x01
#define LCD_BLINKOFF 0x00

// flags for display entry mode
#define LCD_ENTRYRIGHT 0x00
#define LCD_ENTRYLEFT 0x02
#define LCD_ENTRYSHIFTINCREMENT 0x01
#define LCD_ENTRYSHIFTDECREMENT 0x00

// flags for backlight control
#define LCD_BACKLIGHT 0x08
#define LCD_NOBACKLIGHT 0x00

#define En 0x04  // Enable bit
#define Rw 0x02  // Read/Write bit
#define Rs 0x01  // Register select bit

class Display_LCD_I2C : public Print {
    public:
        Display_LCD_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize = LCD_5x8DOTS);

        void begin();

        void home();

        void clear();

        void noDisplay();

        void display();

        void backlight();
        void noBacklight();

        void setCursor(uint8_t, uint8_t);
        virtual size_t write(uint8_t);
        void command(uint8_t);
        void load_custom_character(uint8_t char_num, uint8_t *rows);	
        void createChar(uint8_t, uint8_t[]);
        void setBacklight(uint8_t new_val);	
        void printstr(const char[]);

    private:
        void send(uint8_t, uint8_t);
        void write4bits(uint8_t);
        void expanderWrite(uint8_t);
        void pulseEnable(uint8_t);
        uint8_t _addr;
        uint8_t _displayfunction;
        uint8_t _displaycontrol;
        uint8_t _displaymode;
        uint8_t _cols;
        uint8_t _rows;
        uint8_t _charsize;
        uint8_t _backlightval;
};

#endif // DISPLAY_LCD_I2C_HAL_H