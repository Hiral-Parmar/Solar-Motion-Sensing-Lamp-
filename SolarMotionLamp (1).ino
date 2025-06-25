
const int pirpin = 2;
const int ledpin = 9; // PWM pin

volatile bool motionDetected = false;
bool LedIsOn = false;
unsigned long LastMotionTime = 0;

void wakeUp() {
  motionDetected = true;
  LastMotionTime = millis(); // jab motion detect hua, uss waqt ka time yaad rakho
}

void setup() {
  pinMode(pirpin, INPUT);
  pinMode(ledpin, OUTPUT);

  attachInterrupt(digitalPinToInterrupt(pirpin), wakeUp, RISING); // PIR motion interrupt
  digitalWrite(ledpin, LOW); // Start mein LED band
}

void loop() {
  unsigned long TimeSinceMotion = millis() - LastMotionTime;

  if (TimeSinceMotion < 5000) {
    // Motion ke 5 seconds tak: full brightness
    analogWrite(ledpin, 255);
    LedIsOn = true;
  }
  else if (TimeSinceMotion < 15000) {
    // Motion ke 5-15 seconds baad: dim light
    analogWrite(ledpin, 128);
    LedIsOn = true;
  }
  else {
    // 15 seconds ke baad: LED off
    analogWrite(ledpin, 0);
    LedIsOn = false;
    motionDetected = false; // fir se nayi motion ke liye ready ho jao
  }

  // Loop fast chalega, bas LED ki brightness adjust hoti rahegi based on motion timing
}
