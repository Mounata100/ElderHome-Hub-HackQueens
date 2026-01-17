// mpu6050.c
#include "mpu6050.h"
#include "esp_log.h"

void mpu6050_init() {
    ESP_LOGI("MPU6050", "Initializing MPU-6050 (stub)");
    // TODO: I2C initialization when ESP-IDF ready
}

void mpu6050_read_accel(float* ax, float* ay, float* az) {
    *ax = 0; *ay = 0; *az = 9.8; // placeholder values
}