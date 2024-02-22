#include "Display_LCD_I2C_HAL.h"
#include <Wire.h>

Display_LCD_I2C::Display_LCD_I2C(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows, uint8_t charsize){
	_addr = lcd_addr;
	_cols = lcd_cols;
	_rows = lcd_rows;
	_charsize = charsize;
	_backlightval = LCD_BACKLIGHT;
}

void Display_LCD_I2C::begin(){
    Wire.begin();
    _displayfunction = LCD_4BITMODE | LCD_1LINE | LCD_5x8DOTS;

	if (_rows > 1) {
		_displayfunction |= LCD_2LINE;
	}

	if ((_charsize != 0) && (_rows == 1)) {
		_displayfunction |= LCD_5x10DOTS;
	}

    delay(50);

    expanderWrite(_backlightval);
	delay(1000);

    // start in 8bit mode, try to set 4 bit mode
	write4bits(0x03 << 4);
	delayMicroseconds(4500); // wait min 4.1ms

	// second try
	write4bits(0x03 << 4);
	delayMicroseconds(4500); // wait min 4.1ms

	// third try
	write4bits(0x03 << 4);
	delayMicroseconds(150);

	// finally, set to 4-bit interface
	write4bits(0x02 << 4);

	// set # lines, font size, etc.
	command(LCD_FUNCTIONSET | _displayfunction);

	// turn the display on with no cursor or blinking default
	_displaycontrol = LCD_DISPLAYON | LCD_CURSOROFF | LCD_BLINKOFF;
	display();

	// clear
	clear();

	// Initialize to default text direction
	_displaymode = LCD_ENTRYLEFT | LCD_ENTRYSHIFTDECREMENT;

	// set the entry mode
	command(LCD_ENTRYMODESET | _displaymode);

	home();
}

//  HIGHT COMMANDS LEVEL

void Display_LCD_I2C::clear() {
	command(LCD_CLEARDISPLAY);
	delayMicroseconds(2000);
}

void Display_LCD_I2C::home() {
    command(LCD_RETURNHOME);
    delayMicroseconds(2000);
}

void Display_LCD_I2C::setCursor(uint8_t col, uint8_t row){
    int row_offsets[] = { 0x00, 0x40, 0x14, 0x54 };

	if (row > _rows) {
		row = _rows-1;    // count rows starting w/0
	}
    
	command(LCD_SETDDRAMADDR | (col + row_offsets[row]));
}

void Display_LCD_I2C::backlight(void) {
	_backlightval=LCD_BACKLIGHT;
	expanderWrite(0);
}

// MID COMMANDS LEVEL

inline void Display_LCD_I2C::command(uint8_t value) {
	send(value, 0);
}

inline size_t Display_LCD_I2C::write(uint8_t value) {
	send(value, Rs);
	return 1;
}

// LOW COMMANDS LEVEL

void Display_LCD_I2C::send(uint8_t value, uint8_t mode) {
	uint8_t highnib=value&0xf0;
	uint8_t lownib=(value<<4)&0xf0;
	write4bits((highnib)|mode);
	write4bits((lownib)|mode);
}

void Display_LCD_I2C::write4bits(uint8_t value) {
	expanderWrite(value);
	pulseEnable(value);
}

void Display_LCD_I2C::expanderWrite(uint8_t _data){
	Wire.beginTransmission(_addr);
	Wire.write((int)(_data) | _backlightval);
	Wire.endTransmission();
}

void Display_LCD_I2C::pulseEnable(uint8_t _data){
	expanderWrite(_data | En);
	delayMicroseconds(1);

	expanderWrite(_data & ~En);
	delayMicroseconds(50);
}

void Display_LCD_I2C::load_custom_character(uint8_t char_num, uint8_t *rows){
	createChar(char_num, rows);
}

void Display_LCD_I2C::setBacklight(uint8_t new_val){
	if (new_val) {
		backlight();		// turn backlight on
	} else {
		noBacklight();		// turn backlight off
	}
}

void Display_LCD_I2C::printstr(const char c[]){
	print(c);
}