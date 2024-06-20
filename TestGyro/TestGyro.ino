/*
  Arduino LSM6DS3 - Simple Gyroscope

  This example reads the gyroscope values from the LSM6DS3
  sensor and continuously prints them to the Serial Monitor
  or Serial Plotter.

  The circuit:
  - Arduino Uno WiFi Rev 2 or Arduino Nano 33 IoT

  created 10 Jul 2019
  by Riccardo Rizzo

  This example code is in the public domain.
*/

#include <Arduino_LSM6DS3.h>

void setup() {
  Serial.begin(9600);
  while (!Serial);

  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");

    while (1);
  }

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
}

void loop() {
  float x, y, z;
  float minActiv = 22;

  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  if(x>minActiv || x<-minActiv || y>minActiv || y<-minActiv || z>minActiv || z<-minActiv)
  {
        if(x>0)
    {
      //Serial.print(x);
      Serial.println("Gauche");
    }
    if(x<0)
    {
      //Serial.print(x);
      Serial.println("Droite");
    }
    if(y>0)
    {
      Serial.println("Avant");
    }
    if(y<0)
    {
      Serial.println("Arriere");
    }
    if(z>0)
    {
      Serial.println("Je tourne sur moi même 1");
    }
    if(z<0)
    {
      Serial.println("Je tourne sur moi même 2");
    }
  }



  /*
    Serial.print(x);
    Serial.print('\t');
    Serial.print(y);
    Serial.print('\t');
    Serial.println(z);
    */
  }
}
