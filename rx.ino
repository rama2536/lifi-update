#define DO_PIN   4
#define BIT_TIME 200   
#define POLAR    1      

bool bacaLED() {
  bool raw = digitalRead(DO_PIN);
  return (POLAR == 1) ? raw : !raw;  
}

char terimaChar() {
  delay(BIT_TIME + (BIT_TIME / 2));

  char c = 0;
  for (int i = 0; i < 8; i++) {
    if (bacaLED())
      c |= (1 << i);
    delay(BIT_TIME);
  }

  delay(BIT_TIME);
  return c;
}

void setup() {
  pinMode(DO_PIN, INPUT);
  Serial.begin(9600);
  Serial.println("========================");
  Serial.println("  LiFi RX Siap");
  Serial.println("  BIT_TIME  : 1000 ms");
  Serial.print  ("  Polaritas : POLAR=");
  Serial.println(POLAR);
  Serial.println("  Menunggu data...");
  Serial.println("========================");

  while (false) {
    Serial.print("DO raw=");
    Serial.print(digitalRead(DO_PIN));
    Serial.print("  bacaLED=");
    Serial.println(bacaLED());
    delay(300);
  }
}

String pesanDiterima = "";
int    totalError     = 0;

void loop() {
  if (!bacaLED()) return;  

  Serial.println("[RX] Menerima karakter...");
  char c = terimaChar();

  if (c == '\n') {
    Serial.println();
    Serial.println("========================");
    Serial.print("[RX] Pesan   : ");  Serial.println(pesanDiterima);
    Serial.print("[RX] Panjang : ");  Serial.print(pesanDiterima.length());
    Serial.println(" karakter");
    Serial.print("[RX] Error   : ");  Serial.println(totalError);
    Serial.println(digitalRead(DO_PIN));
    Serial.println("========================");
    pesanDiterima = "";
    totalError    = 0;

  } else if (c >= 32 && c <= 126) {
    pesanDiterima += c;
    Serial.print("[RX] Karakter : ");  Serial.println(c);

  } else {
    totalError++;
    Serial.print("[ERR] byte = ");  Serial.println((int)c);
  }
}