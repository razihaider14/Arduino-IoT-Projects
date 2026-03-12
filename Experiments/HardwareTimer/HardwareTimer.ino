const int ledPin = 18;

hw_timer_t *timer = NULL;

volatile bool toggleFlag = false;

void IRAM_ATTR onTimer() {
  toggleFlag = true;   // keep ISR tiny
}

void setup() {
  pinMode(ledPin, OUTPUT);

  // NEW API (3.x)
  timer = timerBegin(1000);   // 1000 Hz = 1 ms tick

  timerAttachInterrupt(timer, &onTimer);

  timerAlarm(timer, 500, true, 0); 
  // 500 ticks = 500 ms
  // true = repeat
}

void loop() {
  if (toggleFlag) {
    toggleFlag = false;
    digitalWrite(ledPin, !digitalRead(ledPin));
  }
}
