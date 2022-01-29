#include <imu.h>

int servopinx=2;    // dio port definition
int servopiny=5;
int pulsewidth;     // pwm on time
int repeat=1;       // number of pwm write cycle repetition
int ax;             // angle for servo motors
int ay;
int az;
float comp = 1.1;  // compensate not to show minus value
float adj = 30;    // adjuct the angle with map() function not to exceed the range upper limit 180　& eliminate the noise
float p_accX = 0.5;
float p_accY = 0.5;
float p_accZ = 0.5;
boolean first = true;   // check if it is first cycle or not.
float smooth = 0.6;     // smoothing the angle value. it causes a delay time to the angle change.
//
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
void setup()
{
 setup_imu();
 pinMode(servopinx,OUTPUT);
 pinMode(servopiny,OUTPUT);
}
void loop()
{
 loop_imu();
 if (first == true){        // smoothing
     p_accX = accX;
     p_accY = accY;
     p_accZ = accZ;
     first = false;
    }
    else{
        p_accX = p_accX*smooth + accX*(1-smooth);       
        p_accY = p_accY*smooth + accY*(1-smooth);
        p_accZ = p_accZ*smooth + accZ*(1-smooth);
    }
 ax = map((int)((p_accX+comp)*adj), 0, 66, 0, 180);
 ay = map((int)((p_accY+comp)*adj), 0, 66, 0, 180);
 az = map((int)((p_accZ+comp)*adj), 0, 66, 0, 180);
 M5.Lcd.setCursor(0, 114);
 M5.Lcd.printf("%3d  %3d  %3d ", ax, ay, az);
 servo(ax , 0);
 servo(ay , 1);
 delay(5);
}
