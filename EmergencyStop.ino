void processEmergencyStop(unsigned long now)
{
  emergencyStopped =
    digitalRead(EMERGENCY_BUTTON_PIN) == LOW;

  if (emergencyStopped)
  {
    if (now % 500 < 350)
      tone(BUZZER_PIN, 2500);
    else
      noTone(BUZZER_PIN);
  }
  else
  {
    noTone(BUZZER_PIN);
  }
}
