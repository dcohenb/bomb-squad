#include "Keypad_images.h"

LCDWIKI_SPI mylcd(SSD1283A, KEYPAD_LCD_CS, KEYPAD_LCD_CD, -1, KEYPAD_LCD_SDA, KEYPAD_LCD_RST, KEYPAD_LCD_SCK, -1); // Tell the lib what pins we are using

int images[4];
int indices[4];
int mutableIndices[4];

int selected[4] = {0, 0, 0, 0};
bool screenRendered = false;
#define TOTAL_SEQUENCES 5
int sequences[TOTAL_SEQUENCES][7] = {
  {9, 21, 11, 12, 17, 19, 5},
  {24, 9, 5, 7, 10, 19, 2},
  {0, 18, 7, 15, 23, 11, 10},
  {1, 3, 13, 17, 15, 2, 14},
  {6, 14, 13, 4, 3, 26, 27},
  // {1, 24, 8, 22, 6, 25, 16}
};

void keypadSetup() {
  mylcd.Init_LCD();
  mylcd.Fill_Screen(WHITE);

  // select random sequence
  int mutableSequences[TOTAL_SEQUENCES][7];
  memcpy(mutableSequences, sequences, 4 * TOTAL_SEQUENCES * 7);
  int selectedSequence = random(TOTAL_SEQUENCES);
  Serial.println("selectedSequence: " + String(selectedSequence));
  int skipped = 0;
  for(int i = 0; i < 4; i++) {
    // images[i] = sequences[selectedSequence][i]; continue; // Debug select first 4
    int currIndex = random(7);
    int currElement = mutableSequences[selectedSequence][currIndex];
    if (currElement == -1) {
      i--;
    } else {
      images[i] = currElement;  
      indices[i] = currIndex;  
      mutableSequences[selectedSequence][currIndex] = -1;
    }
  }
  memcpy(mutableIndices, indices, 4 * 4);

  Serial.println(
    "IMAGES: " +
    String(images[0]) + "," +
    String(images[1]) + "," +
    String(images[2]) + "," +
    String(images[3])
  );
  Serial.println(
    "BUTTONS: " +
    String(indices[0]) + "," +
    String(indices[1]) + "," +
    String(indices[2]) + "," +
    String(indices[3])
  );
  renderKeypadScreen(); // Initial Render
}

int findSmallest() {
  int smallest = 9999;
  for (int i = 0; i < 4; ++i) {
    if (mutableIndices[i] < smallest) {
      smallest = mutableIndices[i];
    }
  }

  return smallest;
}

void onKeypadButtonDown(int btnNumber){
  Serial.println("Keypad down, number: " + String(btnNumber));

  Serial.println(String(findSmallest()));
  Serial.println(String(mutableIndices[btnNumber]));
  if (mutableIndices[btnNumber] == findSmallest()) {
    mutableIndices[btnNumber] += 1000;
    selected[btnNumber] = 1;

    bool finished = true;
    for (int i = 0; i < 4; ++i) {
      if(selected[i] == 0) {
        finished = false;
        break;
      }
    }
    if(finished) moduleSuccess(2);
  } else {
    addStrike();
    for (int i = 0; i < 4; ++i) {
      selected[i] = 0;
      mutableIndices[i] = indices[i];
    }
  }

  renderKeypadScreen();
} 

void renderKeypadScreen() { 
  // Cross
  mylcd.Set_Draw_color(BLACK);
  mylcd.Draw_Line(0, 64, 129, 64);
  mylcd.Draw_Line(64, 0, 64, 129);

  // Cells
  int index = 0;
  for(int row = 0; row < 2; row++) {
    for(int col = 0; col < 2; col++) {
      mylcd.Set_Draw_color(BLACK);
      _drawKeypadImage(images[index], row, col);

      // Indicator
      mylcd.Set_Draw_color(selected[index] == 1 ? GREEN : selected[index] == -1 ? RED : BLACK);
      mylcd.Fill_Rectangle(col * 64 + 32 - 10, row * 64 + 3, col * 64 + 32 + 10, row * 64 + 13); // indicator light

      index++;
    }
  }
}

void _drawKeypadImage(int imageNumber, int cellRow, int cellCol) {
//  mylcd.Set_Text_colour(BLACK);
//  mylcd.Set_Text_Size(3);
//  mylcd.Print_String(String(imageNumber), cellRow * 64 + 20, cellCol * 64 + 20);

  for(int row = 0; row < 32; row++) {
    for(int col = 0; col < 32; col++) {
      if(bitRead(KEYPAD_IMAGES[imageNumber][row], 32 - col) == 1) {
        mylcd.Draw_Pixel(col + (cellCol * 64 + 16), row + (cellRow * 64 + 23));
      }
    }
  }
}
