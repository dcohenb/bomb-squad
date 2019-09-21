// Main Module
#define STRIKES_PIXELS_PIN   50
#define SUCCESS_PIXELS_PIN   51
#define CLOCK_PIXELS_PIN     52
#define BUZZER_PIN           53
#define PIEZZO_PIN           44
#define VIBRATOR_PIN         12
#define SMALL_VIBRATOR_1_PIN 48
#define SMALL_VIBRATOR_2_PIN 49
#define RANDOM_SEED_PIN      0

// Buzzer Sounds
#define STRIKE_BUZZER_FREQ     100
#define STRIKE_BUZZER_DURATION 1000
#define CLOCK_1_BUZZER_FREQ    1000
#define CLOCK_2_BUZZER_FREQ    900
#define CLOCK_BUZZER_DURATION  100

// Keypad Module
const int KEYPAD_BUTTONS[4] = {
  22, // KEYPAD_BTN_1
  24, // KEYPAD_BTN_2
  26, // KEYPAD_BTN_3
  28  // KEYPAD_BTN_4
};

#define KEYPAD_LCD_CS   3   // Chip Select SPI pin (Might be called SS) - Wire this to pin 10 on an Arduino Pro Mini
#define KEYPAD_LCD_RST  4    // Reset pin - I use 9 on my Pro Mini
#define KEYPAD_LCD_CD   5
#define KEYPAD_LCD_SDA  6   // if you use the hardware spi,this pin is no need to set - Wire this to pin 11, MOSI, on a Pro Mini
#define KEYPAD_LCD_SCK  7     //if you use the hardware spi,this pin is no need to set - Wire to pin 13 on a Pro Mini


// MAZE Module
const int MAZE_BUTTONS[4] = {
  8 , // MAZE_BTN_1 LEFT
  9 , // MAZE_BTN_2 RIGHT
  10, // MAZE_BTN_3 TOP
  11  // MAZE_BTN_4 BOTTOM
};

#define MAZE_LCD_CS   23   // Chip Select SPI pin (Might be called SS) - Wire this to pin 10 on an Arduino Pro Mini
#define MAZE_LCD_RST  25    // Reset pin - I use 9 on my Pro Mini
#define MAZE_LCD_CD   27
#define MAZE_LCD_SDA  29   // if you use the hardware spi,this pin is no need to set - Wire this to pin 11, MOSI, on a Pro Mini
#define MAZE_LCD_SCK  31     //if you use the hardware spi,this pin is no need to set - Wire to pin 13 on a Pro Mini


#define MAIN_LCD_CS   A1   // Chip Select SPI pin (Might be called SS) - Wire this to pin 10 on an Arduino Pro Mini
#define MAIN_LCD_RST  A2    // Reset pin - I use 9 on my Pro Mini
#define MAIN_LCD_CD   A3
#define MAIN_LCD_SDA  A4   // if you use the hardware spi,this pin is no need to set - Wire this to pin 11, MOSI, on a Pro Mini
#define MAIN_LCD_SCK  A5     //if you use the hardware spi,this pin is no need to set - Wire to pin 13 on a Pro Mini

// Password Module
const int PASSWORD_BUTTONS[11] = {
  42, /* PASSWORD_BTN_01 */ 43, /* PASSWORD_BTN_02 */
  34, /* PASSWORD_BTN_03 */ 37, /* PASSWORD_BTN_04 */
  40, /* PASSWORD_BTN_05 */ 41, /* PASSWORD_BTN_06 */
  38, /* PASSWORD_BTN_07 */ 39, /* PASSWORD_BTN_08 */
  36, /* PASSWORD_BTN_09 */ 35, /* PASSWORD_BTN_10 */
                 30 /* SUBMIT_BTN */
};

#define PASSWORD_LCD_SDA   20 // Not used in code but keep free
#define PASSWORD_LCD_SCL   21 // Not used in code but keep free



// Util
#define  WHITE   0xFFFF
#define  BLACK   0x0000
#define  RED     0xF800
#define  GREEN   0x0F80

// State Machine
#define  SUCCESS_NEEDED 3



// Pre-calc
// const int KEYPAD_BUTTONS_ARRAY_LENGTH = sizeof(KEYPAD_BUTTONS) / sizeof(KEYPAD_BUTTONS[0]);
const int KEYPAD_BUTTONS_ARRAY_LENGTH = 6;
const int PASSWORD_BUTTONS_ARRAY_LENGTH = 11;
