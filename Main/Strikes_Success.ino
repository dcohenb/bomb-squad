#define STRIKES_PIXELS_NUM 3
Adafruit_NeoPixel _strikesPixels(STRIKES_PIXELS_NUM, STRIKES_PIXELS_PIN, NEO_GRB + NEO_KHZ800);

int strikes = 0;

void strikeSetup() {
  _strikesPixels.begin();
  _strikesPixels.clear();
  _strikesPixels.show();
}

void addStrike() {
  strikes++;

  _strikesPixels.clear();
  _strikesPixels.fill(_strikesPixels.Color(150, 0, 0), 0, strikes);
  _strikesPixels.show();
}
