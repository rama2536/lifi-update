#define LED_PIN  3
#define BIT_TIME 200   

void kirimBit(bool bit) {
  digitalWrite(LED_PIN, bit ? HIGH : LOW);
  delay(BIT_TIME);
  Serial.print("data= ");
  Serial.print(bit);
  Serial.println("end");
}

void kirimChar(char c) {
  kirimBit(1);
  for (int i = 0; i < 8; i++)
    kirimBit((c >> i) & 1);
  kirimBit(0);
  delay(BIT_TIME);
}

void kirimPesan(String pesan) {
  Serial.print("[TX] Mengirim  : ");  Serial.println(pesan);
  Serial.print("[TX] Estimasi  : ");
  Serial.print(pesan.length() * 10);
  Serial.println(" detik");

  for (int i = 0; i < (int)pesan.length(); i++) {
    kirimChar(pesan[i]);
    Serial.print("[TX] Karakter ke-"); Serial.print(i + 1);
    Serial.print(" : ");               Serial.println(pesan[i]);
  }

  kirimChar('\n');
  Serial.println("[TX] Selesai!");
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.begin(9600);
  Serial.println("========================");
  Serial.println("  LiFi TX Siap");
  Serial.println("  BIT_TIME  : 1000 ms");
  Serial.println("  Idle      : LED mati");
  Serial.println("========================");
  Serial.println("Ketik pesan + Enter");
}

void loop() {
  // digitalWrite(LED_PIN, LOW);
  analogWrite(LED_PIN, 0);
  if (!Serial.available()) return;

  String pesan = Serial.readStringUntil('\n');
  pesan.trim();
  if (pesan.length() > 0)
    kirimPesan(pesan);
}