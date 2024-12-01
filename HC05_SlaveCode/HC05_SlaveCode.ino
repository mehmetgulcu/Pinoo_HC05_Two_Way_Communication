const int ledPin = 2; // LED bağlantı pini

void setup() {
  pinMode(ledPin, OUTPUT); // LED çıkış olarak ayarlandı
  Serial.begin(9600); // Donanımsal UART'ı başlat
  Serial.println("Slave hazır...");
}

void loop() {
  if (Serial.available()) {
    char data = Serial.read(); // Gelen veriyi oku
    Serial.print("Gelen veri: ");
    Serial.println(data);
    if (data == '1') {
      digitalWrite(ledPin, HIGH); // LED'i aç
    } else if (data == '0') {
      digitalWrite(ledPin, LOW); // LED'i kapat
    }
  }
}
