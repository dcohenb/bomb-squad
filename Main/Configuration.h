// Main Module
#define STRIKES_PIXELS_PIN  50
#define SUCCESS_PIXELS_PIN  51
#define CLOCK_PIXELS_PIN    52
#define BUZZER_PIN          53

// Keypad Module
const int KEYPAD_BUTTONS[4] = {
  22, // KEYPAD_BTN_1
  23, // KEYPAD_BTN_2
  24, // KEYPAD_BTN_3
  25  // KEYPAD_BTN_4
};

#define KEYPAD_LCD_CS   26   // Chip Select SPI pin (Might be called SS) - Wire this to pin 10 on an Arduino Pro Mini
#define KEYPAD_LCD_RST  27    // Reset pin - I use 9 on my Pro Mini
#define KEYPAD_LCD_CD   28
#define KEYPAD_LCD_SDA  29   // if you use the hardware spi,this pin is no need to set - Wire this to pin 11, MOSI, on a Pro Mini
#define KEYPAD_LCD_SCK  30     //if you use the hardware spi,this pin is no need to set - Wire to pin 13 on a Pro Mini


// Password Module
const int PASSWORD_BUTTONS[11] = {
  12, /* PASSWORD_BTN_01 */ 11, /* PASSWORD_BTN_02 */
  10, /* PASSWORD_BTN_03 */ 9 , /* PASSWORD_BTN_04 */
  8 , /* PASSWORD_BTN_05 */ 7 , /* PASSWORD_BTN_06 */
  6 , /* PASSWORD_BTN_07 */ 5 , /* PASSWORD_BTN_08 */
  4 , /* PASSWORD_BTN_09 */ 3 , /* PASSWORD_BTN_10 */
                 13 /* SUBMIT_BTN */
};

#define PASSWORD_LCD_SDA   20 // Not used in code but keep free
#define PASSWORD_LCD_SCL   21 // Not used in code but keep free



// Util
#define  WHITE   0xFFFF
#define  BLACK   0x0000
#define  RED     0xF800
#define  GREEN   0x0F80



// Pre-calc
const int KEYPAD_BUTTONS_ARRAY_LENGTH = sizeof(KEYPAD_BUTTONS) / sizeof(KEYPAD_BUTTONS[0]);
const int PASSWORD_BUTTONS_ARRAY_LENGTH = sizeof(PASSWORD_BUTTONS) / sizeof(PASSWORD_BUTTONS[0]);
