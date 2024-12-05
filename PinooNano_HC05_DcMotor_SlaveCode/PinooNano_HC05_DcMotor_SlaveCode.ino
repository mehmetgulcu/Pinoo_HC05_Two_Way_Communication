const int ledPin1 = 2;  // Buton 1'e bağlı LED pini
const int ledPin2 = 3;  // Buton 2'ye bağlı LED pini

const int motorPin1 = 5;       // Motor yönü için kullanılan pin 1
const int motorPin2 = 6;       // Motor yönü için kullanılan pin 2
const int motorEnablePin = 9;  // Motor hız kontrolü için PWM pini

void setup() {
  pinMode(ledPin1, OUTPUT);         // LED 1 pini çıkış olarak ayarlandı
  pinMode(ledPin2, OUTPUT);         // LED 2 pini çıkış olarak ayarlandı
  pinMode(motorPin1, OUTPUT);       // Motor yön pini 1 çıkış olarak ayarlandı
  pinMode(motorPin2, OUTPUT);       // Motor yön pini 2 çıkış olarak ayarlandı
  pinMode(motorEnablePin, OUTPUT);  // Motor hız kontrol pini çıkış olarak ayarlandı

  Serial.begin(9600);  // Seri iletişim başlatıldı
  Serial.println("Slave hazır..."); // Başlangıç mesajı gönderildi
}

void loop() {
  if (Serial.available()) { // Seri port üzerinden veri varsa
    char data = Serial.read();  // Gelen veri karakter olarak okunur
    Serial.print("Gelen veri: ");
    Serial.println(data);       // Gelen veri seri monitöre yazdırılır

    // Gelen veriye göre işlem yapılır
    switch (data) {
      case 'i':                       // Buton 1'e basıldı
        digitalWrite(ledPin1, HIGH);  // LED 1'i yak
        break;
      case 'j':                       // Buton 1 bırakıldı
        digitalWrite(ledPin1, LOW);   // LED 1'i söndür
        break;
      case 'l':                       // Buton 2'ye basıldı
        digitalWrite(ledPin2, HIGH);  // LED 2'yi yak
        break;
      case 'k':                       // Buton 2 bırakıldı
        digitalWrite(ledPin2, LOW);   // LED 2'yi söndür
        break;
      case 'a':  // Joystick ileri hareket
        digitalWrite(motorPin1, HIGH); // Motor yönü ileri
        digitalWrite(motorPin2, LOW);
        analogWrite(motorEnablePin, 200);  // Motor hızı (0-255)
        break;
      case 'd':  // Joystick geri hareket
        digitalWrite(motorPin1, LOW);  // Motor yönü geri
        digitalWrite(motorPin2, HIGH);
        analogWrite(motorEnablePin, 200);  // Motor hızı (0-255)
        break;
      case 'c':  // Joystick sağ hareket
        digitalWrite(motorPin1, HIGH); // Motor yönü sağ
        digitalWrite(motorPin2, LOW);
        analogWrite(motorEnablePin, 150);  // Daha düşük hız (0-255)
        break;
      case 'b':  // Joystick sol hareket
        digitalWrite(motorPin1, LOW);  // Motor yönü sol
        digitalWrite(motorPin2, HIGH);
        analogWrite(motorEnablePin, 150);  // Daha düşük hız (0-255)
        break;
      case 'n':                      // Joystick dur
        digitalWrite(motorPin1, LOW);  // Motoru durdur
        digitalWrite(motorPin2, LOW);
        analogWrite(motorEnablePin, 0); // Hız sıfırlandı
        break;
    }
  }
}
