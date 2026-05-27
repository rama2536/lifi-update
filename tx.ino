#define PWM_PIN 3
#define BIT_TIME 500

// ACTIVE LOW DRIVER
// LOW  = LED ON
// HIGH = LED OFF

void ledOn() {
  digitalWrite(PWM_PIN, LOW);
}

void ledOff() {
  digitalWrite(PWM_PIN, HIGH);
}

void kirimBit(bool bitData) {

  // =================================
  // BIT 1 = LED ON
  // BIT 0 = LED OFF
  // =================================

  if (bitData == 1) {
    ledOn();
  }
  else {
    ledOff();
  }

  delay(BIT_TIME);
}

void kirimChar(char c) {

  Serial.print("KIRIM CHAR : ");
  Serial.println(c);

  // =================================
  // PREAMBLE
  // =================================

  for (int i = 0; i < 6; i++) {

    ledOff();
    delay(100);

    ledOn();
    delay(100);
  }

  // =================================
  // START
  // OFF panjang
  // =================================

  ledOff();

  delay(BIT_TIME * 2);

  // =================================
  // DATA
  // =================================

  Serial.print("BINARY TX : ");

  for (int i = 0; i < 8; i++) {

    bool bitData = (c >> i) & 1;

    Serial.print(bitData);

    kirimBit(bitData);
  }

  Serial.println();

  // kembali idle
  ledOn();
}

void setup() {

  pinMode(PWM_PIN, OUTPUT);

  ledOn();

  Serial.begin(9600);

  Serial.println("TX READY");
}

void loop() {

  if (Serial.available()) {

    char c = Serial.read();

    if (c == '\n' || c == '\r') return;

    kirimChar(c);
  }
}
