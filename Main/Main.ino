#include "Configuration.h"
#include <Adafruit_NeoPixel.h>
#include <LCDWIKI_GUI.h> // Core graphics library
#include <LCDWIKI_SPI.h> // Hardware-specific library

#define GAME_ROUND_TIME 300000 // 5 minutes in milliseconds

int roundSecondsLeft = GAME_ROUND_TIME;
const int RANDOM_PIN = 0;

void setup() {
  randomSeed(analogRead(RANDOM_PIN));
  Serial.begin(9600);
  
  clockSetup();
  strikeSetup();
  passwordSetup();
  keypadSetup();
}

void loop() {
  passwordLoop();
  keypadLoop();
  
  roundSecondsLeft = ((GAME_ROUND_TIME - millis()) / 1000);

  if(roundSecondsLeft < 0) return gameLoose();
  
  int minutes = roundSecondsLeft / 60;
  int seconds = roundSecondsLeft - minutes * 60;

  setClockNumbers((minutes * 100) + seconds);
}

void gameLoose() {
  setClockNumbers(0);
}

void moduleSuccess(int moduleNumber) {
  
}
