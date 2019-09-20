#define CLOCK_PIXELS_PIN 22
#define CLOCK_PIXELS_NUM 37
Adafruit_NeoPixel _clockPixels(CLOCK_PIXELS_NUM, CLOCK_PIXELS_PIN, NEO_GRB + NEO_KHZ800);

const int _clockNumbers[4][10][7] = {
  { // Position 0
    {6,  7,  8, 22, 23, 36, -1 }, // 0
    {8,  23, -1, -1, -1, -1, -1 }, // 1
    {6,  8, 21, 22, 36, -1, -1 }, // 2
    {6,  8, 21, 23, 36, -1, -1 }, // 3
    {-1, 7, 8, 21, -1, 23, -1 }, // 4
    {6, 7, -1, 21, -1, 23, 36 }, // 5 
    {6, 7, -1, 21, 22, 23, 36 }, // 6
    {6, -1, 8, -1, -1, 23, -1 }, // 7
    {6, 7, 8, 21, 22, 23, 36 }, // 8
    {6, 7, 8, 21, -1, 23, 36 } // 9
  },
  { // Position 1
    {4,  9,  10, 24, 25, 34, -1 }, // 0
    {10,  25, -1, -1, -1, -1, -1 }, // 1
    {4,  10, 19, 24, 34, -1, -1 }, // 2
    {4,  10, 19, 25, 34, -1, -1 }, // 3
    {-1, 9, 10, 19, -1, 25, -1 }, // 4
    {4, 9, -1, 19, -1, 25, 34 }, // 5
    {4, 9, -1, 19, 24, 25, 34 }, // 6
    {4, -1, 10, -1, -1, 25, -1 }, // 7
    {4, 9, 10, 19, 24, 25, 34 }, // 8
    {4, 9, 10, 19, -1, 25, 34 } // 9
  },
  { // Position 2
    {2,  11,  12, 26, 27, 32, -1 }, // 0
    {12,  27, -1, -1, -1, -1, -1 }, // 1
    {2,  12, 17, 26, 32, -1, -1 }, // 2
    {2,  12, 17, 27, 32, -1, -1 }, // 3
    {-1, 11, 12, 17, -1, 27, -1 }, // 4
    {2, 11, -1, 17, -1, 27, 32 }, // 5
    {2, 11, -1, 17, 26, 27, 32 }, // 6
    {2, -1, 12, -1, -1, 27, -1 }, // 7
    {2, 11, 12, 17, 26, 27, 32 }, // 8
    {2, 11, 12, 17, -1, 27, 32 } // 9
  },
  { // Position 3
    {0,  13,  14, 28, 29, 30, -1 }, // 0
    {14,  29, -1, -1, -1, -1, -1 }, // 1
    {0,  14, 15, 28, 30, -1, -1 }, // 2
    {0,  14, 15, 29, 30, -1, -1 }, // 3
    {-1, 13, 14, 15, -1, 29, -1 }, // 4
    {0, 13, -1, 15, -1, 29, 30 }, // 5
    {0, 13, -1, 15, 28, 29, 30 }, // 6
    {0, -1, 14, -1, -1, 29, -1 }, // 7
    {0, 13, 14, 15, 28, 29, 30 }, // 8
    {0, 13, 14, 15, -1, 29, 30 } // 9
  }
};

void clockSetup() {
  _clockPixels.begin();
  _clockPixels.clear();
  _clockPixels.show();
}

void setClockNumbers(int number) {
  // Serial.println("setClockNumbers"+ String(number)); 
  _clockPixels.clear();
  _setClockNumber(0, number / 1000);
  _setClockNumber(1, (number / 100) % 10);
  _setClockNumber(2, (number / 10) % 10);
  _setClockNumber(3, number % 10);
  _clockPixels.show();
}

void _setClockNumber(int pos, int number) {
  for(int i = 0; i < 7; i++) {
    if(_clockNumbers[pos][number][i] < 0) continue;
    _clockPixels.setPixelColor(_clockNumbers[pos][number][i], _clockPixels.Color(100, 0, 0));
  }
}
