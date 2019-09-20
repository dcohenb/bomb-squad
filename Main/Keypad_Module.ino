#include "Keypad_images.h"

LCDWIKI_SPI mylcd(SSD1283A, KEYPAD_LCD_CS, KEYPAD_LCD_CD, -1, KEYPAD_LCD_SDA, KEYPAD_LCD_RST, KEYPAD_LCD_SCK, -1); // Tell the lib what pins we are using

int images[4] = {13, 22, 3, 1};
int selected[4] = {0, 0, 0, 0};
bool screenRendered = false;

void keypadSetup() {
  for(int i = 0; i < sizeof(KEYPAD_BUTTONS); i++) {
    pinMode(KEYPAD_BUTTONS[i], INPUT_PULLUP);
  }

  mylcd.Init_LCD();
  mylcd.Fill_Screen(WHITE);

  renderKeypadScreen(); // Initial Render
}

void keypadLoop() {
  // Buttons
  static int lastButtonsStates[KEYPAD_BUTTONS_ARRAY_LENGTH] = {};
  
  for(int i = 0; i < KEYPAD_BUTTONS_ARRAY_LENGTH; i++) {
    int buttonState = digitalRead(KEYPAD_BUTTONS[i]) == LOW ? HIGH : LOW;
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
