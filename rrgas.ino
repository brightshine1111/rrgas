// Intervals in milliseconds
#define ON_MIN 30 * 1000L
#define ON_MAX 60 * 1000L

#define OFF_MIN 10 * 1000L
#define OFF_MAX 10 * 1000L

#define FLICKER_ON_MIN 100L
#define FLICKER_ON_MAX 400L

#define FLICKER_OFF_MIN 100L
#define FLICKER_OFF_MAX 400L

#define FLICKERS_MIN 1L
#define FLICKERS_MAX 7L

#define DEBUG false

void setup() {
  if(DEBUG) Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  on();
  off();
}

void on() {
  // Flicker a random number of times while time remains
  const unsigned long totalTimeOn = (unsigned long)random(ON_MIN, ON_MAX);
  const unsigned long timeFinish = millis() + totalTimeOn;
  long timeRemain = timeFinish - millis();
  while (timeRemain > 0) {
    output(HIGH, "on", random(0, timeRemain));
    flicker();

    timeRemain = timeFinish - millis();
  }
}

void flicker() {
  // Rapidly turn off and on for random intervals, a random number of times
  const long numFlickers = random(FLICKERS_MIN, FLICKERS_MAX);
  for (int i=0; i<numFlickers; i=i+1) {
    output(LOW, "off", random(FLICKER_OFF_MIN, FLICKER_OFF_MAX));
    output(HIGH, "on", random(FLICKER_ON_MIN, FLICKER_ON_MAX));
  }
}

void off() {
  // Disable interrupt
  output(LOW, "off", random(OFF_MIN, OFF_MAX));
}

void output(const uint8_t val, const String valString, const unsigned long wait) {
  digitalWrite(LED_BUILTIN, val);

  if(DEBUG) {
    String msg = valString + ", waiting " + String(wait) + "ms";
    Serial.println(msg);
  }

  delay(wait);
}
