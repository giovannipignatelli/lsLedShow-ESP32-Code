#include <LiquidCrystal_I2C.h>

class LCDOutput {
private:
    LiquidCrystal_I2C lcd; // Create an LCD object. Adjust the address and dimensions as needed.

public:
    LCDOutput(uint8_t lcdAddr, uint8_t lcdCols, uint8_t lcdRows)
        : lcd(lcdAddr, lcdCols, lcdRows) {}

    void begin() {
        lcd.init(); // Initialize the LCD
        lcd.backlight(); // Turn on the backlight
    }

    void clear() {
        lcd.clear(); // Clear the LCD display
    }

    void print(const String &line1, const String &line2 = "") {
        lcd.clear(); // Clear the display before printing new information
        lcd.setCursor(0, 0); // Set cursor to first line
        lcd.print(line1);
        if (!line2.isEmpty()) {
            lcd.setCursor(0, 1); // Set cursor to second line if there is a second line to print
            lcd.print(line2);
        }
    }
};
