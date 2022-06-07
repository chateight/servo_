#include <imu.h>

extern float accX;  // Define variables for storing inertial sensor data
extern float accY;
extern float accZ;

int servopinx=2;    // dio port definition for X axis
int servopiny=5;    // dio port definition for Y axis
int repeat=1;       // number of pwm write cycle repetition
boolean first = true;   // check if it is first cycle or not.
int pulsewidth;     // pwm on time
int ax;             // angle for servo motors
int ay;
int az;
float p_accX;       // to hold IMU read data
float p_accZ;
int p_angX;         // to hold servo motor angles
int p_angZ;


void servo(int myangle, int motor)      // servo motor pwm contorol. motor 0 : servoponx , motor 1 : servopiny
{
 for (int i = 0; i < repeat; i ++)      // i is used to keep a moving time, since this source does not use the library.
 {
    int port;
    if (motor == 0){
        port = servopinx;
         }
        else{
        port = servopiny;
    }
    pulsewidth=map(myangle,0,180,500,2500);
    digitalWrite(port,HIGH);
    delayMicroseconds(pulsewidth);
    digitalWrite(port,LOW);
    delay(20-pulsewidth/1000);
 }
}
void init_sm()
{
    servo(90, 0);
    servo(90, 1);
    p_angX = 90;
    p_angZ = 90;
    delay(600);
}
void setup()
{
 setup_imu();
 setup_batt();
 pinMode(servopinx,OUTPUT);
 pinMode(servopiny,OUTPUT);
}
void loop()
{
 loop_imu();
 if (first == true){
    init_sm();                  // initialize to 90 degree
    first = false;
    }
// the angle change is needed? & the change is reflected? & check the angle limit
 if (accX < -0.05 && abs(p_accX - accX) > 0.02 && p_angX < 180){ p_angX ++; } else{ if (accX > 0.05 && abs(p_accX - accX) > 0.02 && p_angX > 0){
             p_angX --;
         }
     }
 if (accZ < -0.05 && abs(p_accZ - accZ) > 0.02 && p_angZ < 180){ p_angZ ++; } else{ if (accZ > 0.05 && abs(p_accZ - accZ) > 0.02 && p_angZ > 0){
             p_angZ --;
         }
     }
 p_accX = accX;                 // set to the previous values
 p_accZ = accZ;
 servo(p_angZ , 0);             // drive the servo motor
 servo(p_angX , 1);
 delay(1);
 M5.Lcd.setCursor(0, 114);
 M5.Lcd.printf("%3d  %3d ", p_angX, p_angZ);

 // battery level indication
 int bat_level = read_batt();
 M5.Lcd.setCursor(0, 158);
 M5.Lcd.printf("batt_level : %3d %%",bat_level);
}
