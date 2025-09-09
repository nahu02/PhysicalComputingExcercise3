#include "GY521.h"

int photoSensorPin = A0;   // select the input pin for the potentiometer
int photoSensorValue = 0;  // variable to store the value coming from the sensor

int darknessTreshold = 600;
float accelerationTreshold = 2.0;

GY521 sensor(0x68);

uint32_t counter = 0;

bool lightAndMoving(float acceleration, int light) {
  bool isMoving = acceleration > accelerationTreshold;
  bool isDark = light < darknessTreshold;
  
  // char buffer[256];
  // char acc[10];
  // dtostrf(acceleration, 2, 2, acc);
  // snprintf(buffer, sizeof(buffer), "Movement: %s (%s);\tLight: %s (%d)", isMoving ? "moving" : "still", acc, isDark ? "dark" : "light", light);
  // Serial.println(buffer);

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
  photoSensorValue = analogRead(photoSensorPin);
  int acc = readCombinedAcceleration(sensor);

  bool shouldTurnLightOn = lightAndMoving(acc, photoSensorValue);

  Serial.print(counter);
  Serial.print("\tShould the light be on?\t");
  Serial.print(shouldTurnLightOn, BIN);
  Serial.println();

  counter++;
  delay(1000);
}
