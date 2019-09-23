#define STRIKES_PIXELS_NUM 3
// #define SUCCESS_PIXELS_NUM 73
#define SUCCESS_PIXELS_NUM 133

Adafruit_NeoPixel _strikesPixels(STRIKES_PIXELS_NUM, STRIKES_PIXELS_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel _successPixels(SUCCESS_PIXELS_NUM, SUCCESS_PIXELS_PIN, NEO_GRB + NEO_KHZ800);

void strikeSetup() {
  _strikesPixels.begin();
  _strikesPixels.clear();
  _strikesPixels.show();

  _successPixels.begin();
  _successPixels.clear();
  _successPixels.show();
}

void lightLoop() {
  for (int i = 0; i < 3; ++i) {
    _successPixels.setPixelColor(i, 0, gameState[i] == success ? 100 : 0, 0);
  }
  _successPixels.show();
}

void addStrike() {
  strikes++;
  _strikesPixels.clear();
  _strikesPixels.fill(_strikesPixels.Color(100, 0, 0), 0, strikes);
  _strikesPixels.show();

  buzzStrike();
  if (strikes >= 3) gameLoose();
}

void gameLostLights(){
  _successPixels.clear();
  _successPixels.fill(_successPixels.Color(100, 0, 0), 3, SUCCESS_PIXELS_NUM);
  _successPixels.show();
}
void gameWonLights(){
  _successPixels.clear();
  _successPixels.fill(_successPixels.Color(0, 100, 0), 3, SUCCESS_PIXELS_NUM);
  _successPixels.show();
}
