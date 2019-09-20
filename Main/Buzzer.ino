bool alternateClock = false;

void buzzLoop() {
  if (gameLost) buzzStrike();
}
void buzzStrike() {
  tone(BUZZER_PIN, STRIKE_BUZZER_FREQ, STRIKE_BUZZER_DURATION);
}

void buzzClock() {
  if (lastRoundSecondsLeft != roundSecondsLeft) {
    alternateClock = !alternateClock;
    if (alternateClock) {
      tone(BUZZER_PIN, CLOCK_1_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
    } else {
      tone(BUZZER_PIN, CLOCK_2_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
    }
  }
}

void unBuzz() {
  noTone(BUZZER_PIN);
}