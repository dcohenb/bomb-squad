#include "Keypad_images.h"

#define MODEL SSD1283A  // Which controller does your LCD use
#define CS   8   // Chip Select SPI pin (Might be called SS) - Wire this to pin 10 on an Arduino Pro Mini
#define RST  9    // Reset pin - I use 9 on my Pro Mini
#define CD   10
#define SDA  11   // if you use the hardware spi,this pin is no need to set - Wire this to pin 11, MOSI, on a Pro Mini
#define SCK  12     //if you use the hardware spi,this pin is no need to set - Wire to pin 13 on a Pro Mini
#define MOSI SDA    // An alias
#define MISO -1    // unused - my SSD1283A is write-only (no read)
#define LED  -1   // My LED backlight is hard-wired to VCC: if you don't need to control the LED pin,you should set it to -1 and set it to 3.3V

LCDWIKI_SPI mylcd(MODEL,CS,CD, MISO, MOSI, RST, SCK, LED); // Tell the lib what pins we are using

#define  WHITE   0xFFFF
#define  BLACK   0x0000
#define  RED     0xF800
#define  GREEN   0x0F80

const int _KEYPAD_BUTTONS[4] = {
  2, // KEYPAD_BTN_1
  3, // KEYPAD_BTN_2
  4, // KEYPAD_BTN_3
  5  // KEYPAD_BTN_4
};

int images[4] = {13, 22, 3, 1};
int selected[4] = {0, 0, 0, 0};
bool screenRendered = false;

void keypadSetup() {
  for(int i = 0; i < sizeof(_KEYPAD_BUTTONS); i++) {
    pinMode(_KEYPAD_BUTTONS[i], INPUT_PULLUP);
  }

  mylcd.Init_LCD();
  mylcd.Fill_Screen(WHITE);

  renderKeypadScreen(); // Initial Render
}

void keypadLoop() {
  // Buttons
  static int lastButtonsStates[sizeof(_KEYPAD_BUTTONS)] = {};
  for(int i = 0; i < sizeof(_KEYPAD_BUTTONS) / sizeof(_KEYPAD_BUTTONS[0]); i++) {
    int buttonState = digitalRead(_KEYPAD_BUTTONS[i]) == LOW ? HIGH : LOW;
    if(buttonState != lastButtonsStates[i]) {
      if(buttonState == HIGH) _onKeypadButtonDown(i);
      lastButtonsStates[i] = buttonState;
    }
  }
}

void _onKeypadButtonDown(int btnNumber){
  Serial.println("Keypad down, number: " + String(btnNumber));

  selected[btnNumber] = 1;

  renderKeypadScreen();
} 

void renderKeypadScreen() {
  // Cross
  mylcd.Set_Draw_color(BLACK);
  mylcd.Draw_Line(0, 64, 129, 64);
  mylcd.Draw_Line(64, 0, 64, 129);

  // Cells
  int index = 0;
  for(int row = 0; row < 2; row++) {
    for(int col = 0; col < 2; col++) {
      mylcd.Set_Draw_color(BLACK);
      _drawKeypadImage(images[index], row, col);

      // Indicator
      mylcd.Set_Draw_color(selected[index] == 1 ? GREEN : BLACK);
      mylcd.Fill_Rectangle(col * 64 + 32 - 10, row * 64 + 3, col * 64 + 32 + 10, row * 64 + 13); // indicator light

      index++;
    }
  }
}

void _drawKeypadImage(int imageNumber, int cellRow, int cellCol) {
//    mylcd.Set_Text_colour(BLACK);
//    mylcd.Set_Text_Size(3);
//    mylcd.Print_String(String(imageNumber), row * 64 + 30, col * 64 + 10);

  Serial.println("DRAW IMAGE: " + String(imageNumber));
  
  for(int row = 0; row < 32; row++) {
    // Serial.println("");
    for(int col = 0; col < 32; col++) {
      
      // Serial.print(String(  bitRead(KEYPAD_IMAGES[imageNumber][row], col)  ));
      // Serial.print(String(  KEYPAD_IMAGES[imageNumber][row] ));
      
      if(bitRead(KEYPAD_IMAGES[imageNumber][row], 32 - col) == 1) {
        mylcd.Draw_Pixel(col + (cellCol * 64 + 16), row + (cellRow * 64 + 23));
      }
      
    }
  }
}
