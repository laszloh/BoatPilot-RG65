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

#include <BMP280_DEV.h>
#include <MPU9250.h>
#include <NMEAGPS.h>
#include <IBusBM.h>
#include <MadgwickAHRS.h>

constexpr int numServo = 3;
constexpr int servoPin[numServo] = {PB11, PB3, PB10};
Servo servo[numServo];

IBusBM iBus;

constexpr int gpsBaud = 9600;
HardwareSerial Serial2(PA3, PA2);
NMEAGPS gps;
gps_fix fix;

SPIClass spiMaster(PB15, PB14, PB13);
SPISettings masterSettings();
constexpr int csBmp280 = PA8;
constexpr int csMpu9250 = PA10;

BMP280_DEV bmp280(csBmp280, spiMaster);
MPU9250 mpu9250(spiMaster, csMpu9250);

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

  bmp280.begin(SLEEP_MODE, OVERSAMPLING_X16, OVERSAMPLING_X2,
    IIR_FILTER_4, TIME_STANDBY_125MS);
  bmp280.startNormalConversion();

  mpu9250.begin();
  mpu9250.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  mpu9250.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  mpu9250.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_20HZ);
  mpu9250.setSrd(19);

  mpu9250.calibrateAccel();
  mpu9250.calibrateGyro();
  mpu9250.calibrateMag();

  // start the IMU and filter
  filter.begin(25);
}

void loop() {
  static uint32_t microsPrevious;

  int32_t temp;
  uint32_t pres;
  float ax, ay, az;
  float gx, gy, gz;
  float roll, pitch, heading;
  unsigned long microsNow;

  // check if it's time to read data and update the filter
  microsNow = micros();
  if (microsNow - microsPrevious >= microsPerReading) {

    // read raw data from CurieIMU
    mpu9250.readSensor();
    ax = mpu9250.getAccelX_mss();
    ay = mpu9250.getAccelY_mss();
    az = mpu9250.getAccelZ_mss();
    gx = mpu9250.getGyroX_rads();
    gy = mpu9250.getGyroY_rads();
    gz = mpu9250.getGyroZ_rads();

    // update the filter, which computes orientation
    filter.updateIMU(gx, gy, gz, ax, ay, az);

    // print the heading, pitch and roll
    roll = filter.getRoll();
    pitch = filter.getPitch();
    heading = filter.getYaw();

    // increment previous time, so we keep proper pace
    microsPrevious = microsPrevious + microsPerReading;
  }

  bmp280.getTempPres(temp, pres);

  iBus.loop();

  while(gps.available(Serial2))
    fix = gps.read();
}
