void addServoTask(int servoId, int angle)
{
  int nextTail = (queueTail + 1) % 10;

  if (nextTail == queueHead)
    return;

  servoQueue[queueTail].servoId = servoId;
  servoQueue[queueTail].angle = angle;
  queueTail = nextTail;
}

void processServoControl(unsigned long now)
{
  if (!servoActive && queueHead != queueTail)
  {
    ServoTask task = servoQueue[queueHead];
    queueHead = (queueHead + 1) % 10;

    if (task.servoId == 1)
      servo1.write(task.angle);
    else
      servo2.write(task.angle);

    servoActive = true;
    servoStartTime = now;
  }

  if (servoActive &&
      now - servoStartTime >= SERVO_RETURN_TIME_MS)
  {
    moveBothServos(SERVO_WAIT_ANGLE);
    servoActive = false;
  }
}

void moveBothServos(int angle)
{
  servo1.write(angle);
  servo2.write(angle);
}
