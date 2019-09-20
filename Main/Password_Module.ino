const int BUTTONS[11] = {
  112, // PASSWORD_BTN_1
  111, // PASSWORD_BTN_2
  110, // PASSWORD_BTN_3
  19, // PASSWORD_BTN_4
  18, // PASSWORD_BTN_5
  17, // PASSWORD_BTN_6
  16, // PASSWORD_BTN_7
  15, // PASSWORD_BTN_8
  14, // PASSWORD_BTN_9
  13, // PASSWORD_BTN_10
  
  113 // SUBMIT_BTN
};

void passwordSetup() {
//  for(int i = 0; i < 11; i++) {
//    pinMode(BUTTONS[i], INPUT_PULLUP);
//  }
}

void passwordLoop() {
//  static int lastButtonsStates[11] = {};
//  
//  for(int i = 0; i < 11; i++) {
//    int buttonState = digitalRead(BUTTONS[i]) == LOW ? HIGH : LOW;
//    if(buttonState != lastButtonsStates[i]) {
//      if(buttonState == LOW) _onPasswordButtonDown(i);
//      lastButtonsStates[i] = buttonState;
//    }
//  }
}

void _onPasswordButtonDown(int btnNumber){
  Serial.println("Password Button down, number: " + String(btnNumber));
}
