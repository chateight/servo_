#include <imu.h>

static int giBattery = 0;
static int giBatteryOld = 0xFF;

void setup_batt()
{  
  M5.begin();
  M5.Power.begin();
}

int read_batt()
{
  int l_battery = M5.Power.getBatteryLevel();
  return l_battery;
}