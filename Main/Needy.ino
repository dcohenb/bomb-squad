

LCDWIKI_SPI needylcd(SSD1283A, NEEDY_LCD_CS, NEEDY_LCD_CD, -1, NEEDY_LCD_SDA, NEEDY_LCD_RST, NEEDY_LCD_SCK, -1); // Tell the lib what pins we are using

const String DIRECTIONS[4] = {"Top", "Right", "Bottom", "Left"};

int needySecondsLeft = 0;
int needyDirection = 0;
int needyLoop = 0;

void needySetup() {
  needylcd.Init_LCD();
  needylcd.Fill_Screen(WHITE);

  startNeedy();
}

void needyOnEverySecond() {
  needySecondsLeft--;

  if(needySecondsLeft == 0) {
    needyFail();
    return;
  }
  
  // Render
  needylcd.Set_Text_colour(BLACK);
  needylcd.Set_Text_Size(3);

  static int lastNeedyLoop = 0;
  if(needyLoop != lastNeedyLoop) {
    lastNeedyLoop = needyLoop;
    needylcd.Fill_Screen(WHITE);
    needylcd.Print_String(DIRECTIONS[needyDirection], 0, 64);      
  }
  needylcd.Print_String(needySecondsLeft < 10 ? "0" + String(needySecondsLeft) : String(needySecondsLeft), 0, 0);  
}

void startNeedy() {
//  successModules--;
  gameState[1] = neutral;
  needySecondsLeft = 30;
  needyDirection = random(4);
  needyLoop++;
}


void onNeedyButtonDown(int i) {
  if(i == needyDirection) needySuccess();
  else needyFail();
}

void needySuccess() {
  Serial.println("Needy SUCCESS");
//  moduleSuccess(1);
  needylcd.Fill_Screen(GREEN);
  startNeedy();
}

void needyFail() {
  Serial.println("Needy FAIL");
  addStrike();
  startNeedy();
  needylcd.Fill_Screen(RED);
}
