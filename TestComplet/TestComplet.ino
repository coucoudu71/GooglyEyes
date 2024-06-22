#include <Arduino_LSM6DS3.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <Math.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 100000);

void welcomeGoogly() {
  display.clearDisplay();
  display.setTextSize(3);      // Normal 1:1 pixel scale
  display.setTextColor(SH110X_WHITE); // Draw white text
  display.setCursor(30, 0);     // Start at top-left corner
  display.cp437(true);         // Use full 256 char 'Code Page 437' font

  display.write("GOOGLY");
  display.display();
  delay(2000);
}

#define rayonCercle 20

void affiche(int X_, int Y_)
{
  display.clearDisplay();
  display.fillCircle(X_, Y_, rayonCercle, SH110X_INVERSE);
  display.display();
}

void setup()   {

  Serial.begin(9600);
  while (!Serial);
  if(!IMU.begin())  {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  Serial.println("Setup complete!");
  

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.accelerationSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
  Serial.println("Setup complete!");

  welcomeGoogly();
  //delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3D default
  display.clearDisplay();
}

float pitchOld, rollOld;

void loop()
{
  float xAcc, yAcc, zAcc;
  float roll, pitch;
  int X = 64;
  int Y = 64;
  if(IMU.accelerationAvailable()){
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    pitch = -atan(xAcc/zAcc)*180/3.1415;
    roll = atan(yAcc/zAcc)*180/3.1415;

    //float pitchFiltered = 0.1 * pitch + 0.9 * pitchFilteredOld; // low pass filter
    //pitchFilteredOld = pitchFiltered;
    ///////////////////////////////////////PITCH X////////////////////////////////////////////////
    if(pitch>pitchOld  && (X+pitch)<128-rayonCercle || pitch<pitchOld && (X+pitch)>rayonCercle)
    {
      X+=pitch;
      pitchOld=pitch;
    }
    else
    {
      //Serial.println("AAAAAAAAAA");
      X+=pitchOld;
    }

    ////////////////////////////////ROLL Y//////////////////////////////////////////////
    if(roll>rollOld && (Y+roll)<128-rayonCercle || roll<rollOld && (Y+roll)>rayonCercle)
    {
      Y+=roll;
      rollOld=roll;
    }
    else
    {
      Y+=rollOld;
    }

    affiche(X,Y);
    delay(10);
    Serial.println("PITCH : " + String(pitch) + "       ROLL : " + String(roll) + "  " + String(X) + "  " + String(Y) + "    " + String(rollOld));
    

  }
}