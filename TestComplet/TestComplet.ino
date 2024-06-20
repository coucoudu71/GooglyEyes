#include <Arduino_LSM6DS3.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include <MadgwickAHRS.h>
#include <Math.h>

#define SCREEN_WIDTH 128  // OLED display width, in pixels
#define SCREEN_HEIGHT 128 // OLED display height, in pixels
#define OLED_RESET -1     // can set an oled reset pin if desired
Adafruit_SH1107 display = Adafruit_SH1107(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET, 1000000, 100000);
float pitchFilteredOld;
float rollFilteredOld;
Madgwick filter;
const float sensorRate = 104.00;

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
  filter.begin(sensorRate);
  Serial.println("Setup complete!");
  

  Serial.print("Gyroscope sample rate = ");
  Serial.print(IMU.gyroscopeSampleRate());
  Serial.println(" Hz");
  Serial.println();
  Serial.println("Gyroscope in degrees/second");
  Serial.println("X\tY\tZ");
  filter.begin(sensorRate);
  Serial.println("Setup complete!");

  delay(250); // wait for the OLED to power up
  display.begin(0x3C, true); // Address 0x3D default
  display.display();
  delay(2000);
  display.clearDisplay();
  testdrawchar("TEST","OK","1");      // Draw characters of the default font
}

float pitchOld, rollOld;

void loop()
{
  float xAcc, yAcc, zAcc;
  float xGyro, yGyro, zGyro;
  float roll, pitch;
  int X = 64;
  int Y = 64;
  if(IMU.accelerationAvailable() && IMU.gyroscopeAvailable()){
    IMU.readAcceleration(xAcc, yAcc, zAcc);
    IMU.readGyroscope(xGyro, yGyro, zGyro); 
    filter.updateIMU(xGyro, yGyro, zGyro, xAcc, yAcc, zAcc);
    pitch = filter.getPitch();
    roll = filter.getRoll();

    //float pitchFiltered = 0.1 * pitch + 0.9 * pitchFilteredOld; // low pass filter
    //pitchFilteredOld = pitchFiltered;
    ///////////////////////////////////////PITCH X////////////////////////////////////////////////
    if(pitch>pitchOld  && (X+pitch)<128 || pitch<pitchOld && (X+pitch)>0)
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
    if(roll>rollOld && (Y+roll)<128 || roll<rollOld && (Y+roll)>0)
    {
      Y+=roll;
      rollOld=roll;
    }
    else
    {
      Y+=rollOld;
    }

    affiche(X,Y);
    Serial.println("PITCH : " + String(pitch) + "       ROLL : " + String(roll) + "  " + String(X) + "  " + String(Y) + "    " + String(rollOld));
    

  }
}