// Intervals in milliseconds
#define RUN_MIN 30 * 1000L
#define RUN_MAX 60 * 1000L

#define WAIT_MIN 1 * 60 * 1000L
#define WAIT_MAX 2 * 60 * 1000L

#define DEBUG false

void setup() {
  if(DEBUG) Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  randomSeed(analogRead(0));
}

void loop() {
  off(random(WAIT_MIN, WAIT_MAX));
  on(random(RUN_MIN, RUN_MAX));
}

void off(const unsigned long wait) {
  digitalWrite(LED_BUILTIN, LOW);
  output("off", wait);
}

void on(const unsigned long wait) {
  digitalWrite(LED_BUILTIN, HIGH);
  output("on", wait);
}

void output(const String val, const unsigned long wait) {
  if(DEBUG) {
    String msg = val + ", waiting " + String(wait) + "ms";
    Serial.println(msg);
  }
  delay(wait);
}
