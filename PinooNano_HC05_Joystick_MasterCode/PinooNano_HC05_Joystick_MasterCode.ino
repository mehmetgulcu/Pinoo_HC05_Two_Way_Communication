const int buttonPin1 = 2; // Buton 1 için bağlantı pini
bool lastButtonState1 = LOW; // Buton 1'in son durumu
const int buttonPin2 = 3; // Buton 2 için bağlantı pini
bool lastButtonState2 = LOW; // Buton 2'nin son durumu

const int Joystick1A = A2; // Joystick 1 Y ekseni pini
const int Joystick1B = A3; // Joystick 1 X ekseni pini
const int Joystick2A = A4; // Joystick 2 Y ekseni pini
const int Joystick2B = A5; // Joystick 2 X ekseni pini

const int threshold = 50; // Joystick merkez değerinden sapma hassasiyet eşiği

void setup() {
  pinMode(buttonPin1, INPUT); // Buton 1 pini giriş olarak ayarlandı
  pinMode(buttonPin2, INPUT); // Buton 2 pini giriş olarak ayarlandı

  pinMode(Joystick1A, INPUT); // Joystick 1 Y ekseni pini giriş olarak ayarlandı
  pinMode(Joystick1B, INPUT); // Joystick 1 X ekseni pini giriş olarak ayarlandı
  pinMode(Joystick2A, INPUT); // Joystick 2 Y ekseni pini giriş olarak ayarlandı
  pinMode(Joystick2B, INPUT); // Joystick 2 X ekseni pini giriş olarak ayarlandı

  Serial.begin(9600); // Seri iletişim başlatıldı
  Serial.println("Master hazır...");
}

void loop() {
  // Joystick 1 ve 2 eksen verilerini oku
  int joy1_Y = analogRead(Joystick1A); // Joystick 1 Y ekseni
  int joy1_X = analogRead(Joystick1B); // Joystick 1 X ekseni
  int joy2_Y = analogRead(Joystick2A); // Joystick 2 Y ekseni
  int joy2_X = analogRead(Joystick2B); // Joystick 2 X ekseni

  // Joystick 1 yönlerine göre veri gönder
  if (joy1_Y > 512 + threshold) {
    Serial.println("a"); // Joystick 1 ileri
  } else if (joy1_Y < 512 - threshold) {
    Serial.println("d"); // Joystick 1 geri
  } else if (joy1_X > 512 + threshold) {
    Serial.println("c"); // Joystick 1 sağ
  } else if (joy1_X < 512 - threshold) {
    Serial.println("b"); // Joystick 1 sol
  } else {
    Serial.println("n"); // Joystick 1 dur
  }

  // Joystick 2 yönlerine göre veri gönder
  if (joy2_Y > 512 + threshold) {
    Serial.println("a"); // Joystick 2 ileri
  } else if (joy2_Y < 512 - threshold) {
    Serial.println("d"); // Joystick 2 geri
  } else if (joy2_X > 512 + threshold) {
    Serial.println("c"); // Joystick 2 sağ
  } else if (joy2_X < 512 - threshold) {
    Serial.println("b"); // Joystick 2 sol
  } else {
    Serial.println("n"); // Joystick 2 dur
  }

  // Buton 1 durumunu kontrol et ve veri gönder
  bool btn1State = digitalRead(buttonPin1); // Buton 1'in mevcut durumu
  if (btn1State != lastButtonState1) { // Buton 1 durumu değiştiyse
    if (btn1State == HIGH) {
      Serial.println("i");  // Buton 1'e basıldığında veri gönder
    } else {
      Serial.println("j");  // Buton 1 bırakıldığında veri gönder
    }
    lastButtonState1 = btn1State; // Buton 1'in son durumunu güncelle
  }

  // Buton 2 durumunu kontrol et ve veri gönder
  bool btn2State = digitalRead(buttonPin2); // Buton 2'nin mevcut durumu
  if (btn2State != lastButtonState2) { // Buton 2 durumu değiştiyse
    if (btn2State == HIGH) {
      Serial.println("l");  // Buton 2'ye basıldığında veri gönder
    } else {
      Serial.println("k");  // Buton 2 bırakıldığında veri gönder
    }
    lastButtonState2 = btn2State; // Buton 2'nin son durumunu güncelle
  }

  delay(100); // İletişim ve işlemleri sabitlemek için küçük bir gecikme
}
