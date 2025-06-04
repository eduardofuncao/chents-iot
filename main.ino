#include <WiFi.h>
#include <ThingerESP32.h>
#include <DHT.h>

// Thinger.io credentials
#define USERNAME "eduardofuncao"
#define DEVICE_ID "chents"
#define DEVICE_CREDENTIAL "&wGIeX@Fa6YwUYZJ"

// Pin definitions
#define DHTPIN 15          // DHT22 data
#define DHTTYPE DHT22      
#define WATER_LEVEL_PIN 34 // Analog pin
#define BUZZER_PIN 2       // Digital pin
#define LED_PIN 4          // Digital pin
#define LDR_PIN 35         // Analog pin

// Thresholds
#define WATER_LEVEL_THRESHOLD 3000
#define LDR_NIGHT_THRESHOLD 1800

// Thinger.io client
ThingerESP32 thing(USERNAME, DEVICE_ID, DEVICE_CREDENTIAL);

// DHT sensor
DHT dht(DHTPIN, DHTTYPE);

float humidity;
float temperature;
int waterLevel;
bool isAlertActive = false;
int ldrValue = 0;
bool isNight = false;

void setup() {
  Serial.begin(115200);
  
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_PIN, LOW);
  dht.begin();

  thing.add_wifi("Wokwi-GUEST", "");  // Wokwi's WiFi credentials
  thing["sensors"] >> [](pson& out){
    out["temperature"] = temperature;
    out["humidity"] = humidity;
    out["waterLevel"] = waterLevel;
    out["isNight"] = isNight;
    out["ldrValue"] = ldrValue;
    out["alert"] = isAlertActive;
  };
  thing["buzzer"] << [](pson& in){
    if(in.is_empty()){
      in = (bool)digitalRead(BUZZER_PIN);
    }
    else{
      digitalWrite(BUZZER_PIN, in ? HIGH : LOW);
    }
  };
  
  Serial.println("Chents - Flood monitoring system initialized");
}

void loop() {
  readSensors();
  
  checkWaterLevel();
  
  thing.handle();
  
  delay(2000);
}

void readSensors() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  waterLevel = analogRead(WATER_LEVEL_PIN);

  ldrValue = analogRead(LDR_PIN);
  isNight = (ldrValue > LDR_NIGHT_THRESHOLD);

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print("°C, Humidity: ");
  Serial.print(humidity);
  Serial.print("%, Water Level: ");
  Serial.print(waterLevel);
  Serial.print(", LDR: ");
  Serial.print(ldrValue);
  Serial.print(", Night: ");
  Serial.println(isNight ? "YES" : "NO");
}

void checkWaterLevel() {
  if (waterLevel > WATER_LEVEL_THRESHOLD) {
    if (!isAlertActive) {
      Serial.println("ALERT: Water level exceeds threshold!");
      isAlertActive = true;
    }
    digitalWrite(LED_PIN, HIGH);
  } else {
    if (isAlertActive) {
      Serial.println("Water level normal");
      isAlertActive = false;
    }
    digitalWrite(LED_PIN, LOW);
  }
}
