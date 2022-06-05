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

void setup_imu();
void setup_batt();
void loop_imu();
int read_batt();