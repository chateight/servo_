/*
*******************************************************************************
* Copyright (c) 2021 by M5Stack
*                  Equipped with M5Core sample source code
* Visit the website for more information：https://docs.m5stack.com/en/core/gray
*
* describe：MPU6886 example. 
* date：2021/7/21
*******************************************************************************
*/
#define M5STACK_MPU6886
#include <M5Stack.h>

float accX = 0.0F;  // Define variables for storing inertial sensor data
float accY = 0.0F;
float accZ = 0.0F;

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
