#include "Configuration.h"
#include <Adafruit_NeoPixel.h>
#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_SPI.h> // Hardware-specific library

#define GAME_ROUND_TIME 302000 // 5 minutes in milliseconds

enum moduleState {
  neutral,
  success
};

int roundSecondsLeft = GAME_ROUND_TIME / 1000;
int lastRoundSecondsLeft = GAME_ROUND_TIME / 1000;
bool gameLost = false;
int strikes = 0;

moduleState gameState[3] = {neutral, success, neutral};
int successModules = 0;

void setup() {
  randomSeed(analogRead(RANDOM_SEED_PIN));
  Serial.begin(9600);
  pinMode(SMALL_VIBRATOR_1_PIN, OUTPUT);
  pinMode(SMALL_VIBRATOR_2_PIN, OUTPUT);

  for(int i = 0; i < TOTAL_BUTTONS; i++) {
    pinMode(BUTTONS[i], INPUT_PULLUP);  
  }

  clockSetup();
  strikeSetup();
  passwordSetup();
  keypadSetup();
  needySetup();
}

void loop() {
  if (!gameLost) {
    // Buttons Loop
    static int lastKeypadButtonsState[TOTAL_BUTTONS] = {};
    for(int i = 0; i < TOTAL_BUTTONS; i++) {
      int buttonState = digitalRead(BUTTONS[i]) == LOW ? HIGH : LOW;
      if(buttonState != lastKeypadButtonsState[i]) {
        if(buttonState == HIGH) {
          if(i < 4) {
            Serial.println("Keypad Button: " + String(i)); // Keypad
            onKeypadButtonDown(i);
          } else if (i < 8) {
            Serial.println("Maze Button: " + String(i - 4)); // Maze
            onNeedyButtonDown(i - 4);
          } else {
            Serial.println("Password Button: " + String(i - 8)); // Password
            onPasswordButtonDown(i - 8);
          }
        }
        lastKeypadButtonsState[i] = buttonState;
      }
    }
    
    if (successModules == SUCCESS_NEEDED) {
      gameWin();
      successModules++;
    } else if (successModules < SUCCESS_NEEDED) {
      lightLoop();
      
      roundSecondsLeft = ((GAME_ROUND_TIME - (millis() * (strikes * 2 + 2))) / 1000);
      // roundSecondsLeft = (GAME_ROUND_TIME - millis()) / 1000;
      
      if(roundSecondsLeft != lastRoundSecondsLeft) {
        if(roundSecondsLeft < 0) return gameLoose();
      
        int minutes = roundSecondsLeft / 60;
        int seconds = roundSecondsLeft - minutes * 60;
  
        setClockNumbers(((minutes * 100) + seconds));
        buzzClock();
  
        needyOnEverySecond();

        lastRoundSecondsLeft = roundSecondsLeft;
      }
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
