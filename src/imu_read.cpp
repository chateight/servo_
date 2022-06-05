#include <imu.h>

float accX;  // Define variables for storing inertial sensor data
float accY;
float accZ;

void setup_imu(){
  M5.begin(); //Init M5Core.  
  M5.Power.begin(); //Init Power module.  

  M5.IMU.Init();  //Init IMU sensor.  

  M5.Lcd.fillScreen(BLACK); //Set the screen background color to black. 
  M5.Lcd.setTextColor(GREEN , BLACK); //Sets the foreground color and background color of the displayed text.  
  M5.Lcd.setTextSize(2);  //Set the font size.  
}

void loop_imu() {
  M5.IMU.getAccelData(&accX,&accY,&accZ); //Stores the triaxial accelerometer. 

  // Accelerometer output is related
  M5.Lcd.setCursor(0, 70);
  M5.Lcd.printf("accX,   accY,  accZ");
  M5.Lcd.setCursor(0, 92);
  M5.Lcd.printf("%5.2f  %5.2f  %5.2f G", accX, accY, accZ);
}
