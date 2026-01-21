#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include <Wire.h>
#include <RTClib.h>
#include <FirebaseESP32.h>

// Firebase configuration
//#define FIREBASE_HOST ""
//#define FIREBASE_AUTH ""
//#define FIREBASE_PATH ""

// Define pins for DHT11, L293D, LEDs, and water pump
#define DHT_PIN 2
#define FAN_ENABLE 
#define RED_LED 5
#define BLUE_LED 6
#define AIR_PUMP_ENABLE 2
#define WATER_LEVEL_SENSOR 5
#define WATER_PUMP_ENABLE 18

// Define constants
#define DHT_TYPE DHT11
#define WATER_LEVEL_THRESHOLD 500 //Half
#define FAN_SPEED_INCREASE 255 // Maximum speed

RTC_DS3231 rtc;
DHT_Unified dht(DHT_PIN, DHT_TYPE);
FirebaseData firebaseData;

void setup() {
  // Initialize serial communication
  Serial.begin(115200);

  // Initialize sensors
  dht.begin();
  Wire.begin();
  rtc.begin();


  // Set pin modes
  pinMode(FAN_ENABLE, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);
  pinMode(AIR_PUMP_ENABLE, OUTPUT);
  pinMode(WATER_PUMP_ENABLE, OUTPUT);

  // Initialize Firebase
//  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
}

void loop() {
  DateTime now = rtc.now();
  float temperature = readTemperature();

  // Turn on fan if temperature increases
  if (temperature > 25.0) {
    increaseFanSpeed();
  } else {
    decreaseFanSpeed();
  }

  // Control lights based on time
  if (now.hour() >= 8 && now.hour() < 20) {
    turnOnLights();
  } else {
    turnOffLights();
  }

  // Control air pump based on time
  if ((now.hour() >= 7 && now.hour() < 8) || (now.hour() >= 20 && now.hour() < 21)) {
    turnOnAirPump();
  } else {
    turnOffAirPump();
  }

  // Check water level and control water pump
  int waterLevel = analogRead(WATER_LEVEL_SENSOR);
  if (waterLevel < WATER_LEVEL_THRESHOLD) {
    turnOnWaterPump();
  } else {
    turnOffWaterPump();
  }

  // Bluetooth control
  if (Serial.available() >= 2) {
    char command = Serial.read();
    if (command == 'A' || command == 'a') {
      // Control Appliance A (Fan)
      toggleFan();
    } else if (command == 'B' || command == 'b') {
      // Control Appliance B (Air Pump)
      toggleAirPump();
    }
  }

  // Send data to Firebase
//  sendDataToFirebase(temperature, waterLevel);

  delay(1000); // Update every second
}

float readTemperature() {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (!isnan(event.temperature)) {
    return event.temperature;
  } else {
    return 0.0;
  }
}

void increaseFanSpeed() {
  analogWrite(FAN_ENABLE, FAN_SPEED_INCREASE);
}

void decreaseFanSpeed() {
  analogWrite(FAN_ENABLE, 0);
}

void turnOnLights() {
  digitalWrite(RED_LED, HIGH);
  digitalWrite(BLUE_LED, HIGH);
}

void turnOffLights() {
  digitalWrite(RED_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
}

void turnOnAirPump() {
  digitalWrite(AIR_PUMP_ENABLE, HIGH);
}

void turnOffAirPump() {
  digitalWrite(AIR_PUMP_ENABLE, LOW);
}

void turnOnWaterPump() {
  digitalWrite(WATER_PUMP_ENABLE, HIGH);
}

void turnOffWaterPump() {
  digitalWrite(WATER_PUMP_ENABLE, LOW);
}

void toggleFan() {
  if (analogRead(FAN_ENABLE) == 0) {
    increaseFanSpeed();
  } else {
    decreaseFanSpeed();
  }
}

void toggleAirPump() {
  if (digitalRead(AIR_PUMP_ENABLE) == LOW) {
    turnOnAirPump();
  } else {
    turnOffAirPump();
  }
}

//void sendDataToFirebase(float temperature, int waterLevel) {
  // Build the data JSON object
  //String data = "{";
  //data += "\"temperature\":" + String(temperature) + ",";
  //data += "\"water_level\":" + String(waterLevel);
  //data += "}";

  // Send data to Firebase
  //Firebase.pushString(firebaseData, FIREBASE_PATH, data);
}
