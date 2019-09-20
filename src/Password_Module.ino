const int BUTTONS[11] = {
  12, // PASSWORD_BTN_1
  11, // PASSWORD_BTN_2
  10, // PASSWORD_BTN_3
  9, // PASSWORD_BTN_4
  8, // PASSWORD_BTN_5
  7, // PASSWORD_BTN_6
  6, // PASSWORD_BTN_7
  5, // PASSWORD_BTN_8
  4, // PASSWORD_BTN_9
  3, // PASSWORD_BTN_10
  
  13 // SUBMIT_BTN
};

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
