bool alternateClock = false;
bool alternateVibrator = false;

void buzzLoop() {
  if (gameLost) buzzStrike();
}
void buzzStrike() {
  tone(BUZZER_PIN, STRIKE_BUZZER_FREQ, STRIKE_BUZZER_DURATION);
  tone(PIEZZO_PIN, STRIKE_BUZZER_FREQ, STRIKE_BUZZER_DURATION);
  digitalWrite(SMALL_VIBRATOR_1_PIN, HIGH);
  digitalWrite(SMALL_VIBRATOR_2_PIN, HIGH);
  delay(1000);
  digitalWrite(SMALL_VIBRATOR_1_PIN, LOW);
  digitalWrite(SMALL_VIBRATOR_2_PIN, LOW);
}

void buzzClock() {
  alternateClock = !alternateClock;
  if (alternateClock) {
    tone(BUZZER_PIN, CLOCK_1_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
    tone(PIEZZO_PIN, CLOCK_1_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
  } else {
    tone(BUZZER_PIN, CLOCK_2_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
    tone(PIEZZO_PIN, CLOCK_2_BUZZER_FREQ, CLOCK_BUZZER_DURATION);
  }
}
