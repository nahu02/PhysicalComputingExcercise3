#include "GY521.h"

int photoSensorPin = A0;   // select the input pin for the potentiometer
int photoSensorValue = 0;  // variable to store the value coming from the sensor

int darkness = 600;

GY521 sensor(0x68);

uint32_t counter = 0;


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
  sensor.setAccelSensitivity(0.5);  //  2g
}

void loop() {
  // read the value from the sensor:
  photoSensorValue = analogRead(photoSensorPin);

  sensor.read();
  float ax = sensor.getAccelX();
  float ay = sensor.getAccelY();
  float az = sensor.getAccelZ();

  float acc = abs(ax) + abs(ay) + abs(az);

  Serial.print(counter);
  Serial.print('\t');
  if(acc > 2) {Serial.print("moving");} else {Serial.print("still");}
  Serial.print('\t');
  if(photoSensorValue < darkness) {Serial.print("dark");} else {Serial.print("light");}
  Serial.println();

  counter++;
  delay(1000);
}
