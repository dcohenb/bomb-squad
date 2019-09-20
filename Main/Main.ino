#include "Configuration.h"
#include <Adafruit_NeoPixel.h>
#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_SPI.h> // Hardware-specific library

#define GAME_ROUND_TIME 300000 // 5 minutes in milliseconds
// #define GAME_ROUND_TIME 10000 // 5 minutes in milliseconds

enum moduleState {
  neutral,
  success
};

int roundSecondsLeft = GAME_ROUND_TIME;
int lastRoundSecondsLeft = GAME_ROUND_TIME;
bool gameLost = false;
int strikes = 0;

moduleState gameState[3] = {neutral, neutral, neutral};
int successModules = 0;

void setup() {
  randomSeed(analogRead(RANDOM_SEED_PIN));
  Serial.begin(9600);
  
  clockSetup();
  strikeSetup();
  passwordSetup();
  keypadSetup();
  gameWonLights();
}

void loop() {
  if (!gameLost) {
    if (successModules == SUCCESS_NEEDED) {
      gameWin();
      successModules++;
    } else if (successModules < SUCCESS_NEEDED) {
      passwordLoop();
      keypadLoop();
      
      roundSecondsLeft = ((GAME_ROUND_TIME - ((millis() - 2000) * (strikes * 2 + 1))) / 1000);

      if(roundSecondsLeft < 0) return gameLoose();
      
      int minutes = roundSecondsLeft / 60;
      int seconds = roundSecondsLeft - minutes * 60;

      setClockNumbers(((minutes * 100) + seconds));
      buzzClock();

      lastRoundSecondsLeft = roundSecondsLeft;
    }
  } else {
    buzzLoop();
    delay(1200);
  }
}

void gameLoose() {
  gameLost = true;
  gameLostLights();
}

void gameWin() {
  gameWonLights();
}

void moduleSuccess(int moduleNumber) {
  gameState[moduleNumber] = success;
  successModules++;
}

void buttonsLoop(int pinArray[], void (*callback)(int btnNumber)) {
  static int lastButtonsPinStates[54] = {};
  
  for(int i = 0; i < sizeof(pinArray) / sizeof(pinArray[0]); i++) {
    int btnPinNumber = pinArray[i];
    int buttonState = digitalRead(btnPinNumber) == LOW ? HIGH : LOW;
    if(buttonState != lastButtonsPinStates[btnPinNumber]) {
      if(buttonState == HIGH) {
        callback(i);
      }
      lastButtonsPinStates[btnPinNumber] = buttonState;
    }
  }  
}
