// mpu6050.h
#pragma once
void mpu6050_init();
void mpu6050_read_accel(float* ax, float* ay, float* az);