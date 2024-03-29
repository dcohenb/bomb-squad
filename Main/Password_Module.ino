#include <Wire.h>  
#include <LiquidCrystal_I2C.h>

const String PASSWORDS[35] = {"about","after","again","below","could",
                              "every","first","found","great","house",
                              "large","learn","never","other","place",
                              "plant","point","right","small","sound",
                              "spell","still","study","their","there",
                              "these","thing","think","three","water",
                              "where","which","world","would","write"};



const int LETTER_SLOT_SIZE = 5;

int slotState[5];

char letterSlots[5][LETTER_SLOT_SIZE];

LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

String chosenWord = "";

bool isActive = false;

void passwordSetup() {
  lcd.begin(16,2);
  lcd.backlight();
  initWord();
  initState();
  initSlots();
  printCurrWord();
  isActive = true;

  Serial.println(getCurrWord());
  Serial.println(chosenWord);
}

void initWord() {
  chosenWord = PASSWORDS[random(35)];
}

void initState() {
  for (int i = 0; i < 5; ++i) {
    slotState[i] = random(LETTER_SLOT_SIZE);
  }
}

void initSlots() {
  String letters = "abcdefghijklmnopqrstuvwxyz";
  for (int i = 0; i < chosenWord.length(); ++i) {
    letters.replace(String(chosenWord[i]), "");
  }

  for (int i = 0; i < chosenWord.length(); ++i) {
    String currLetters = String(letters);
    for (int j = 0; j < LETTER_SLOT_SIZE; ++j) {
      char letterIndex = random(currLetters.length());
      char currLetter = currLetters[letterIndex];
      currLetters.remove(letterIndex, 1);
      letterSlots[i][j] = currLetter;
    }
    letterSlots[i][0] = chosenWord[i];
  }
}

String getCurrWord() {
  char word[5];
  for (int i = 0; i < 5; ++i) {
    word[i] = letterSlots[i][slotState[i]];
  }
  return word;
}

void printCurrWord() {
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print(letterSlots[0][slotState[0]]);
  lcd.setCursor(3, 0);
  lcd.print(letterSlots[1][slotState[1]]);
  lcd.setCursor(7, 0);
  lcd.print(letterSlots[2][slotState[2]]);
  lcd.setCursor(11, 0);
  lcd.print(letterSlots[3][slotState[3]]);
  lcd.setCursor(15, 0);
  lcd.print(letterSlots[4][slotState[4]]);
}

void cyclicHandler(int slot, int direction, int max = 4) {
  if (isActive) {
    slotState[slot] += direction;
    if (slotState[slot] > max) {
      slotState[slot] = 0;
    } else if (slotState[slot] < 0) {
      slotState[slot] = max;
    }
  }
}

void onPasswordButtonDown(int btnNumber){
  Serial.println("Password Button down, number: " + String(btnNumber));
  switch (btnNumber) {
    case 0:
      cyclicHandler(0, 1);
      break;
    case 1:
      cyclicHandler(0, -1);
      break;
    case 2:
      cyclicHandler(1, 1);
      break;
    case 3:
      cyclicHandler(1, -1);
      break;
    case 4:
      cyclicHandler(2, 1);
      break;
    case 5:
      cyclicHandler(2, -1);
      break;
    case 6:
      cyclicHandler(3, 1);
      break;
    case 7:
      cyclicHandler(3, -1);
      break;
    case 8:
      cyclicHandler(4, -1);
      break;
    case 9:
      cyclicHandler(4, -1);
      break;
    case 10:
      if (!checkCurrCorrect()) {
        addStrike();
      } else {
        moduleSuccess(0);
      }
      break;
  }

  printCurrWord();
  Serial.println("Curr State:");
  Serial.println(getCurrWord());
}

bool checkCurrCorrect() {
  bool passed = true;
  for (int i = 0; i < 4; ++i) {
    if (slotState[i] != 0) {
      passed = false;
      break;
    }
  }

  return passed;
}
