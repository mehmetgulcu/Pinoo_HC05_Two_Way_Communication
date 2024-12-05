const int buttonPin = 2;  // Buton bağlantı pini
bool lastButtonState = LOW; // Önceki buton durumu

void setup() {
  pinMode(buttonPin, INPUT);  // Buton giriş olarak ayarlandı
  Serial.begin(9600);         // Donanımsal UART'ı başlat
  Serial.println("Master hazır...");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);  // Butona basılma durumu

  if (buttonState != lastButtonState) { // Buton durumu değiştiyse
    if (buttonState == HIGH) {
      Serial.println("1");  // Butona basıldığında "1" gönder
    } else {
      Serial.println("0");  // Buton bırakıldığında "0" gönder
    }
    lastButtonState = buttonState; // Önceki durumu güncelle
  }

  // delay(10); // Gerekli olmadıkça kaldırabilirsiniz
}
