/*********************************************************************
  This is an example for our Monochrome OLEDs based on SH1107 drivers

  This example is for a 128x128 size display using I2C to communicate

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada  for Adafruit Industries.
  BSD license, check license.txt for more information
  All text above, and the splash screen must be included in any redistribution
*********************************************************************/


#include <Arduino_LSM6DS3.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 100000);


void setup()   {

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

  delay(250); // wait for the OLED to power up

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.

  display.begin(0x3C, true); // Address 0x3D default
 //display.setContrast (0); // dim display
 
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

  // draw a single pixel
  //display.drawPixel(10, 10, SH110X_WHITE);
  // Show the display buffer on the hardware.
  // NOTE: You _must_ call display after making any drawing commands
  // to make them visible on the display hardware!
  testdrawchar("TEST","OK","1");      // Draw characters of the default font
}

void loop() {
  float x, y, z;
  float minActiv = 22;
  char* msgX;
  char* msgY;
  char* msgZ;


  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x, y, z);
  if(x>minActiv || x<-minActiv || y>minActiv || y<-minActiv || z>minActiv || z<-minActiv)
  {
        if(x>0)
    {
      //Serial.print(x);
      Serial.println("Gauche");
      msgX="Gauche";
    }
    if(x<0)
    {
      //Serial.print(x);
      Serial.println("Droite");
      msgX="Droite";
    }
    if(y>0)
    {
      Serial.println("Avant");
      msgY="Avant";
    }
    if(y<0)
    {
      Serial.println("Arriere");
      msgY="Arriere";
    }
    if(z>0)
    {
      Serial.println("Je tourne sur moi même 1");
      msgZ="Je tourne antih";
    }
    if(z<0)
    {
      Serial.println("Je tourne sur moi même 2");
      msgZ="Je tourne horaire";
    }
    testdrawchar(msgX,msgY,msgZ);
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

void testdrawchar(char* x, char* y, char* z) {
  display.clearDisplay();

  display.setTextSize(2);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(0, 20);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  // Not all the characters will fit on the display. This is normal.
  // Library will draw what it can and the rest will be clipped.
  display.write(x);
  display.write('\n');
  display.write(y);
  display.write('\n');
  display.write(z);
  display.write('\n');
  display.display();
}