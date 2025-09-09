#include "GY521.h"
#include <MovingAverage.h>

int photoSensorPin = A0;
int ledPin = LED_BUILTIN;

int darknessTreshold = 600;
float accelerationTreshold = 2.0;

GY521 sensor(0x68);

MovingAverage<float, float> accMA;
MovingAverage<uint16_t, uint16_t> lightMA;

bool lightAndMoving(float acceleration, int light) {
  bool isMoving = acceleration > accelerationTreshold;
  bool isDark = light < darknessTreshold;
  
  char buffer[256];
  char acc[10];
  dtostrf(acceleration, 2, 2, acc);
  snprintf(buffer, sizeof(buffer), "\tMovement: %s (%s)\tLight: %s (%d)", isMoving ? "moving" : "still", acc, isDark ? "dark" : "light", light);
  Serial.println(buffer);

  return isMoving && isDark;
}

int readCombinedAcceleration(GY521 sensor) {
  sensor.readAccel();
  float ax = sensor.getAccelX();
  float ay = sensor.getAccelY();
  float az = sensor.getAccelZ();

  return (abs(ax) + abs(ay) + abs(az));
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  accMA.begin();
  lightMA.begin();

  pinMode(ledPin, OUTPUT);

  delay(100);
  while (sensor.wakeup() == false)
  {
    Serial.print(millis());
    Serial.println("\tCould not connect to GY521: please check the GY521 address (0x68/0x69)");
    delay(1000);
  }
  sensor.reset();
}

void loop() {
  lightMA.add(analogRead(photoSensorPin));
  accMA.add(readCombinedAcceleration(sensor));

  bool shouldTurnLightOn = lightAndMoving(accMA.readAverage(5), lightMA.readWeightedAverage(5));

  Serial.print("Should the light be on?\t");
  Serial.print(shouldTurnLightOn ? "YES" : "NO");
  Serial.println();

  digitalWrite(ledPin, shouldTurnLightOn ? HIGH : LOW);

  delay(1000);
}
