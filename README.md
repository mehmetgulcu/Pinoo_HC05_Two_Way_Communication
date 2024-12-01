# HC-05 Bluetooth Modüllerinin Master ve Slave Olarak Yapılandırılması

Bu proje, iki HC-05 Bluetooth modülünü AT komutları kullanarak Master ve Slave modlarına yapılandırmayı ve ardından Arduino ile iletişim kurmayı amaçlar. Modüller arasında veri alışverişi sağlamak için bir modül Master, diğeri ise Slave olarak ayarlanır. Proje, bağlantı ve kodlama süreçlerini detaylı bir şekilde açıklamaktadır.

---

## Gereksinimler

- 2 adet HC-05 Bluetooth modülü
- Arduino UNO (veya uyumlu bir mikrodenetleyici)
- Breadboard ve bağlantı kabloları
- LED ve direnç (Slave cihaz için)
- Buton (Master cihaz için)
- Bilgisayar ve Arduino IDE

---

## Adımlar

### 1. HC-05 Modülünü AT Moduna Alma

1. **Bağlantılar**: HC-05 modülünü Arduino'ya aşağıdaki şekilde bağlayın:
   - **VCC** → 5V
   - **GND** → GND
   - **TXD** → Arduino RX (D0)
   - **RXD** → Arduino TX (D1)

2. **AT Moduna Geçiş**:
   - HC-05 üzerindeki **butona basılı tutun**.
   - Modülün butonuna basılı tutarken, Arduino'yu bilgisayara bağlayın.
   - LED'in uzun aralıklarla yanıp sönmesi, AT moduna geçildiğini gösterir.

---

### 2. Slave Cihazı Yapılandırma

1. Arduino IDE'de **Serial Monitor**'ü başlatın. İletişim hızını `38400 baud` olarak ayarlayın.
2. Aşağıdaki AT komutlarını sırayla göndererek yanıtları doğrulayın:
   - **Test Komutu**: `AT`
     - Yanıt: `OK`
   - **Baud Hızını Kontrol**: `AT+UART?`
     - Yanıt: `+UART:38400,0,0`
   - **Rol Kontrolü**: `AT+ROLE?`
     - Yanıt: `+ROLE=0` (Slave modunda olduğunu gösterir)
   - **Adres Bilgisi**: `AT+ADDR?`
     - Yanıt: `98d3:34:905d3f` (Bluetooth modülünün adresi)

---

### 3. Master Cihazı Yapılandırma

1. Master cihaz için aynı şekilde AT moduna geçin ve aşağıdaki komutları kullanarak yapılandırmayı tamamlayın:
   - **Baud Hızını Kontrol**: `AT+UART?`
     - Yanıt: `+UART:38400,0,0`
   - **Rol Ayarı**: `AT+ROLE=1`
     - Yanıt: `OK`
   - **Bağlantı Modu**: `AT+CMODE=0`
     - Yanıt: `OK`
   - **Slave Adresi ile Eşleştirme**: `AT+BIND=98d3,34,905d3f`
     - Yanıt: `OK` (Slave modülünün adresi girilmeli)

---

## Arduino Kodları

### Master Kod

Bu kod, bir butona basıldığında Slave modülüne veri gönderir.

```cpp
const int buttonPin = 2;  // Buton bağlantı pini
bool buttonState;

void setup() {
  pinMode(buttonPin, INPUT);  // Buton giriş olarak ayarlandı
  Serial.begin(9600);         // Donanımsal UART'ı başlat
  Serial.println("Master hazır...");
}

void loop() {
  bool buttonState = digitalRead(buttonPin);  // Butona basılma durumu

  if (buttonState == HIGH) {
    Serial.println("1");  // Butona basıldığında "1" gönder
  } else {
    Serial.println("0");  // Buton bırakıldığında "0" gönder
  }
  delay(50);  // Debouncing
}
```

### Slave Kod

Bu kod, Master modülünden gelen veriyi alır ve LED'i kontrol eder.

```cpp
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
