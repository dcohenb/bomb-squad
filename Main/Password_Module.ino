#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

const int BUTTONS[11] = {
  12, /* PASSWORD_BTN_01 */ 11, /* PASSWORD_BTN_02 */
  10, /* PASSWORD_BTN_03 */ 9 , /* PASSWORD_BTN_04 */
  8 , /* PASSWORD_BTN_05 */ 7 , /* PASSWORD_BTN_06 */
  6 , /* PASSWORD_BTN_07 */ 5 , /* PASSWORD_BTN_08 */
  4 , /* PASSWORD_BTN_09 */ 3 , /* PASSWORD_BTN_10 */
                 13 /* SUBMIT_BTN */
};

const int ARRAY_LENGTH = sizeof(BUTTONS) / sizeof(BUTTONS[0]);
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

// the 8 arrays that form each segment of the custom numbers

void passwordSetup() {
  for(int i = 0; i < 11; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);
  }
}

void passwordLoop() {
  static int lastButtonsStates[11] = {};
  
  for(int i = 0; i < 11; i++) {
    int buttonState = digitalRead(BUTTONS[i]) == LOW ? HIGH : LOW;
    if(buttonState != lastButtonsStates[i]) {
      if(buttonState == LOW) _onPasswordButtonDown(i);
      lastButtonsStates[i] = buttonState;
    }
  }
}

void _onPasswordButtonDown(int btnNumber){
  Serial.println("Password Button down, number: " + String(btnNumber));
}
