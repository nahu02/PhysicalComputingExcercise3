# Prototype of automatic bike lamp.

Vertical only prototype of a bike lamp that turns on when and only when it is both dark and the bike is in motion. In other cases (`NOT(dark AND moving)`) the lamp is off.

## Physical components

- ATmega328p with 16MHz external crystal (logic)
- Light Dependent Resistor using a voltage divider circuit (analog sensing)
- GY-521 IMU Gyro/Accelerometer (digital sensing)
- A Light Emitting Diode (LED) with appropriate protection
- Can be powered by an Arduino

## Software components
Documentation on the IMU library is available [here](https://github.com/RobTillaart/GY521).
Documentation on the MovingAverage library is available [here](https://github.com/Zone-of-Engineering-Newcomers/MovingAverage/tree/main/docs).

