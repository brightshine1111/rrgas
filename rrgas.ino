#define ANALOG_READ_MAX 1023

// Intervals in milliseconds
#define ON_MIN 30 * 1000L
#define ON_MAX 60 * 1000L

#define OFF_MIN 1 * 60 * 1000L
#define OFF_MAX 5 * 60 * 1000L

#define FLICKER_ON_MIN 100L
#define FLICKER_ON_MAX 400L

#define FLICKER_OFF_MIN 10L
#define FLICKER_OFF_MAX 100L

#define FLICKERS_MIN 1L
#define FLICKERS_MAX 7L

#define DEBUG true

void setup() {
  if(DEBUG) Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  on();
  off();
  randomSeed(analogRead(0));
}

void on() {
  // Flicker a random number of times while time remains
  const unsigned long totalTimeOn = (unsigned long)random(ON_MIN, ON_MAX);
  const unsigned long timeFinish = millis() + totalTimeOn;
  long timeRemain = timeFinish - millis();

  debug("total time on " + String(totalTimeOn));

  while (timeRemain > 0) {
    output(HIGH, "on", random(0, timeRemain/2));
    flicker();

    timeRemain = timeFinish - millis();
  }
}

void flicker() {
  // Rapidly turn off and on for random intervals, a random number of times
  const long numFlickers = random(FLICKERS_MIN, FLICKERS_MAX);

  debug("flickering " + String(numFlickers) + " times");

  output(LOW, "off-flicker", random(FLICKER_OFF_MIN, FLICKER_OFF_MAX));
  for (int i=0; i<numFlickers; i=i+1) {
    output(HIGH, "on-flicker", random(FLICKER_ON_MIN, FLICKER_ON_MAX));
    output(LOW, "off-flicker", random(FLICKER_OFF_MIN, FLICKER_OFF_MAX));
  }
}

void off() {
  const int timeOffScale = analogRead(A5);
  const unsigned long timeOffMin = timeOffScale * OFF_MIN / ANALOG_READ_MAX;
  const unsigned long timeOffMax = timeOffScale * OFF_MAX / ANALOG_READ_MAX;

  debug("Measured value " + String(timeOffScale)
    + " for timeOffMin " + String(timeOffMin)
    + " and timeOffMax " + String(timeOffMax));

  output(LOW, "off", random(timeOffMin, timeOffMax));
}

void output(const uint8_t val, const String valString, const unsigned long wait) {
  digitalWrite(LED_BUILTIN, val);

  debug(valString + ", waiting " + String(wait) + "ms");

  delay(wait);
}

void debug(const String msg) {
  if(DEBUG) Serial.println(msg);
}
