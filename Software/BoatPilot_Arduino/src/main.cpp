/**
 * @file main.cpp
 * @author Laszlo Hegedüs (laszlo.hegedues@gmail.com)
 * @brief 
 * @version 0.1
 * @date 2020-06-30
 * 
 * \copyright Copyright (c) 2020 under the MIT License
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include <Arduino.h>
#include <SPI.h>
#include <Servo.h>

#include <TinyGPS++.h>
#include <IBusBM.h>
#include <MadgwickAHRS.h>

static float convertRawAcceleration(int aRaw);
static float convertRawGyro(int gRaw);

constexpr int numServo = 3;
constexpr int servoPin[numServo] = {PB11, PB3, PB10};
Servo servo[numServo];

IBusBM iBus;

constexpr int gpsBaud = 9600;
HardwareSerial Serial2(PA3, PA2);
TinyGPSPlus tinyGps;

SPIClass spiMaster(PB15, PB14, PB13);
SPISettings masterSettings();
constexpr int csBmp280 = PA8;
constexpr int csMpu9250 = PA10;

Madgwick filter;
constexpr int microsPerReading = 25;

void setup() {
  Serial.begin(9600);
  while(!Serial.available());

  // connect the servos
  for(int i=0;i<numServo;i++)
    servo[i].attach(servoPin[i]);

  // setup IBus on UART1
  Serial1.enableHalfDuplexRx();
  iBus.begin(Serial1, IBUSBM_NOTIMER);

  Serial2.begin(gpsBaud);

  // enable the SPI2 as master
  spiMaster.begin();
  pinMode(csBmp280, OUTPUT);
  digitalWrite(csBmp280, HIGH);

  pinMode(csMpu9250, OUTPUT);
  digitalWrite(csMpu9250, HIGH);

  // start the IMU and filter
  filter.begin(25);
}

void loop() {
  static uint32_t microsPrevious;

  int aix, aiy, aiz;
  int gix, giy, giz;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    // read raw data from CurieIMU
    aix = aiy = aiz = gix = giy = giz = 0x200;

    // convert from raw data to gravity and degrees/second units
    ax = convertRawAcceleration(aix);
    ay = convertRawAcceleration(aiy);
    az = convertRawAcceleration(aiz);
    gx = convertRawGyro(gix);
    gy = convertRawGyro(giy);
    gz = convertRawGyro(giz);

    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();
    Serial.print("Orientation: ");
    Serial.print(heading);
    Serial.print(" ");
    Serial.print(pitch);
    Serial.print(" ");
    Serial.println(roll);

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
  }

  iBus.loop();

  while(Serial2.available() > 0)
    tinyGps.encode(Serial2.read());
}

float convertRawAcceleration(int aRaw) {
  // since we are using 2G range
  // -2g maps to a raw value of -32768
  // +2g maps to a raw value of 32767
  
  float a = (aRaw * 2.0) / 32768.0;
  return a;
}

float convertRawGyro(int gRaw) {
  // since we are using 250 degrees/seconds range
  // -250 maps to a raw value of -32768
  // +250 maps to a raw value of 32767
  
  float g = (gRaw * 250.0) / 32768.0;
  return g;
}