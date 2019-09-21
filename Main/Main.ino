#include "Configuration.h"
#include <Adafruit_NeoPixel.h>
#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_SPI.h> // Hardware-specific library

#define GAME_ROUND_TIME 300000 // 5 minutes in milliseconds

enum moduleState {
  neutral,
  success
};

int roundSecondsLeft = GAME_ROUND_TIME;
int lastRoundSecondsLeft = GAME_ROUND_TIME;
bool gameLost = false;
int strikes = 0;

moduleState gameState[3] = {neutral, success, neutral};
int successModules = 0;

void setup() {
  randomSeed(analogRead(RANDOM_SEED_PIN));
  Serial.begin(9600);
  pinMode(SMALL_VIBRATOR_1_PIN, OUTPUT);
  pinMode(SMALL_VIBRATOR_2_PIN, OUTPUT);

  clockSetup();
  strikeSetup();
  passwordSetup();
  keypadSetup();
}

void loop() {
  if (!gameLost) {
    if (successModules == SUCCESS_NEEDED) {
      gameWin();
      successModules++;
    } else if (successModules < SUCCESS_NEEDED) {
      passwordLoop();
      keypadLoop();
      lightLoop();
      
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
    unBuzz();
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
