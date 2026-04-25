#define BLYNK_TEMPLATE_ID "TMPL3xp3BajCU"
#define BLYNK_TEMPLATE_NAME "Tampering Detection"
#define BLYNK_AUTH_TOKEN "I1RS54YXxhkydaK_bNkriyq3bAaI6jFQ"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include "HX711.h"

// WiFi
char ssid[] = "Shivani";
char pass[] = "shivanihb";

// LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);

// HX711
#define DT 4
#define SCK 5
HX711 scale;

// Sensors
#define VIB_SENSOR 13
#define LIMIT_SWITCH 26

// Outputs
#define BUZZER 14
#define LED 27

float weight = 0;
bool tamper = false;

void setup() {
  Serial.begin(115200);

  Wire.begin(21, 22);

  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print("System Starting");
  delay(2000);
  lcd.clear();

  pinMode(VIB_SENSOR, INPUT);
  pinMode(LIMIT_SWITCH, INPUT_PULLUP);
  pinMode(BUZZER, OUTPUT);
  pinMode(LED, OUTPUT);

  digitalWrite(BUZZER, LOW);
  digitalWrite(LED, LOW);

  // HX711
  scale.begin(DT, SCK);
  delay(500);
  scale.tare();

  // WiFi (non-blocking)
  WiFi.begin(ssid, pass);
  int timeout = 0;
  while (WiFi.status() != WL_CONNECTED && timeout < 10) {
    delay(1000);
    Serial.println("Connecting WiFi...");
    timeout++;
  }

  // Blynk
  Blynk.config(BLYNK_AUTH_TOKEN);
  Blynk.connect(3000);

  Serial.println("Setup Done");
}

void loop() {
  Blynk.run();

  // HX711 SAFE READ
  if (scale.is_ready()) {
    long raw = scale.read();
    weight = abs((raw - scale.get_offset()) / 10000.0);
  } else {
    Serial.println("HX711 NOT READY");
    weight = 0;
  }

  // Sensor read
  int vib = digitalRead(VIB_SENSOR);
  int limit = digitalRead(LIMIT_SWITCH);

  tamper = (vib == HIGH || limit == LOW);

  // LCD DISPLAY
  lcd.setCursor(0, 0);
  lcd.print("Wt:");
  lcd.print(weight);
  lcd.print("kg   ");

  lcd.setCursor(0, 1);

  if (tamper) {
    lcd.print("TAMPER ALERT   ");
    digitalWrite(BUZZER, HIGH);
    digitalWrite(LED, HIGH);

    // Blynk alert
    Blynk.virtualWrite(V1, "Tamper Detected");
    Blynk.logEvent("tamper_alert", "Tampering Detected!");
  } 
  else {
    lcd.print("Status: Normal ");
    digitalWrite(BUZZER, LOW);
    digitalWrite(LED, LOW);

    Blynk.virtualWrite(V1, "Normal");
  }

  // Send weight
  Blynk.virtualWrite(V0, weight); 

  delay(500);
}
