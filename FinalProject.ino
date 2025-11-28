// -----------------------------------------------------------
// IR Sensor + LM35 + Water Level + Buzzer
// -----------------------------------------------------------

// IR Sensor + LED Pins
int IRSensor = 8;
int LED = 11;

// Buzzer Pin
int Buzzer = 5;

// LM35 Temperature Sensor + Red LED
int LM35_Pin = A1;
int RedLED = 13;

// Water Level Sensor Pin (Moved to A2)
int WaterLevel_Pin = A2;

void setup() {
  pinMode(IRSensor, INPUT);
  pinMode(LED, OUTPUT);
  pinMode(RedLED, OUTPUT);
  pinMode(Buzzer, OUTPUT);

  Serial.begin(9600);
  delay(1000);
  Serial.println("IR + LM35 + Water Level Monitoring System Started!");
}

void loop() {

  // ---------------------------
  // IR SENSOR + BUZZER
  // ---------------------------
  int sensorStatus = digitalRead(IRSensor);

  if (sensorStatus == 0) {
    digitalWrite(LED, HIGH);
    digitalWrite(Buzzer, HIGH);
    Serial.println("Object Detected!");
  } else {
    digitalWrite(LED, LOW);
    digitalWrite(Buzzer, LOW);
    Serial.println("No Object in Sight");
  }

  // ---------------------------
  // LM35 TEMPERATURE
  // ---------------------------
  int rawValue = analogRead(LM35_Pin);
  float voltage = (rawValue / 1023.0) * 5.0;
  float temperatureC = voltage * 100.0;

  Serial.print("Temperature (°C): ");
  Serial.println(temperatureC);

  if (temperatureC > 30) {
    Serial.println("Livestock temperature is HIGH!");
  } else if (temperatureC < 25) {
    Serial.println("Livestock temperature is LOW!");
  } else {
    Serial.println("Livestock temperature is NORMAL.");
  }

  if (temperatureC > 30 && temperatureC < 49) {
    digitalWrite(RedLED, HIGH);
  } else {
    digitalWrite(RedLED, LOW);
  }

  // ---------------------------
  // WATER LEVEL SENSOR
  // ---------------------------
  int waterRaw = analogRead(WaterLevel_Pin);
  float tankLevel = map(waterRaw, 0, 1023, 0, 100);

  Serial.print("Tank Level: ");
  Serial.print(tankLevel);
  Serial.println("%");

  Serial.println("---------------------------------------");
  delay(800);
}
