#define RX_PIN 4
#define BIT_TIME 500

bool bacaSensor() {

  return digitalRead(RX_PIN);
}

bool detectStart() {

  if (bacaSensor() == LOW) {

    unsigned long t0 = millis();

    while (bacaSensor() == LOW) {

      if (millis() - t0 >= (BIT_TIME * 2)) {

        return true;
      }
    }
  }

  return false;
}

char bacaChar() {

  char data = 0;

  String binaryRX = "";

  while (!detectStart());

  Serial.println("START DETECTED");

  // menuju tengah bit pertama
  delay(BIT_TIME / 2);

  for (int i = 0; i < 8; i++) {

    bool level = bacaSensor();

    bool bitData;

    // =================================
    // HIGH = LED ON  = bit 1
    // LOW  = LED OFF = bit 0
    // =================================

    if (level == HIGH) {
      bitData = 1;
    }
    else {
      bitData = 0;
    }

    binaryRX += String(bitData);

    data |= (bitData << i);

    delay(BIT_TIME);
  }

  Serial.print("BINARY RX : ");
  Serial.println(binaryRX);

  return data;
}

void setup() {

  pinMode(RX_PIN, INPUT_PULLUP);

  Serial.begin(115200);

  Serial.println("RX READY");
}

void loop() {

  char c = bacaChar();

  Serial.print("HASIL RX : ");
  Serial.println(c);
}
