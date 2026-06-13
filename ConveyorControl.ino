void processInfraredSensor(unsigned long now)
{
  int sensorState = digitalRead(IR_SENSOR_PIN);

  if (sensorState == LOW)
  {
    if (sensorLowStartTime == 0)
      sensorLowStartTime = now;

    bool debounceFinished =
      now - sensorLowStartTime >= SENSOR_DEBOUNCE_TIME_MS;

    if (sensorArmed &&
        !objectDetected &&
        debounceFinished)
    {
      objectDetected = true;
      conveyorStopStartTime = now;
      sensorArmed = false;
    }
  }
  else
  {
    sensorLowStartTime = 0;
    sensorArmed = true;
  }

  if (objectDetected &&
      now - conveyorStopStartTime >= CONVEYOR_STOP_TIME_MS)
  {
    objectDetected = false;
    conveyorStopStartTime = 0;
  }
}

void controlConveyorMotor()
{
  bool mustStop =
    emergencyStopped ||
    pcTimeout ||
    systemRunning == 0 ||
    objectDetected;

  if (mustStop)
  {
    analogWrite(MOTOR_A_PIN, 0);
    analogWrite(MOTOR_B_PIN, 0);

    digitalWrite(MOTOR_A_PIN, LOW);
    digitalWrite(MOTOR_B_PIN, LOW);

    return;
  }

  analogWrite(MOTOR_A_PIN, MOTOR_PWM);
  digitalWrite(MOTOR_B_PIN, LOW);
}
