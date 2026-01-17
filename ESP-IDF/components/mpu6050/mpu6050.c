// mpu6050.c
/*
#include "mpu6050.h"
#include "esp_log.h"

void mpu6050_init() {
    ESP_LOGI("MPU6050", "Initializing MPU-6050 (stub)");
    // TODO: I2C initialization when ESP-IDF ready
}

void mpu6050_read_accel(float* ax, float* ay, float* az) {
    *ax = 0; *ay = 0; *az = 9.8; // placeholder values
}
    */
#include "mpu6050.h"
#include "esp_log.h"
#include "driver/i2c.h"

#define I2C_MASTER_NUM I2C_NUM_0
#define MPU6050_ADDR 0x68
#define I2C_MASTER_SDA_IO 8  // Adjust to your board
#define I2C_MASTER_SCL_IO 9
#define I2C_MASTER_FREQ_HZ 100000

static const char* TAG = "MPU6050";

void mpu6050_init() {
    i2c_config_t conf = {
        .mode = I2C_MODE_MASTER,
        .sda_io_num = I2C_MASTER_SDA_IO,
        .scl_io_num = I2C_MASTER_SCL_IO,
        .sda_pullup_en = GPIO_PULLUP_ENABLE,
        .scl_pullup_en = GPIO_PULLUP_ENABLE,
        .master.clk_speed = I2C_MASTER_FREQ_HZ,
    };
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);

    // Wake up MPU6050
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x6B, true);  // PWR_MGMT_1 register
    i2c_master_write_byte(cmd, 0x00, true);  // Wake up
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    ESP_LOGI(TAG, "MPU6050 initialized");
}

void mpu6050_read_accel(float* ax, float* ay, float* az) {
    uint8_t data[6];
    i2c_cmd_handle_t cmd = i2c_cmd_link_create();
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_WRITE, true);
    i2c_master_write_byte(cmd, 0x3B, true);  // ACCEL_XOUT_H
    i2c_master_start(cmd);
    i2c_master_write_byte(cmd, (MPU6050_ADDR << 1) | I2C_MASTER_READ, true);
    i2c_master_read(cmd, data, 6, I2C_MASTER_LAST_NACK);
    i2c_master_stop(cmd);
    i2c_master_cmd_begin(I2C_MASTER_NUM, cmd, pdMS_TO_TICKS(1000));
    i2c_cmd_link_delete(cmd);

    *ax = (int16_t)((data[0] << 8) | data[1]) / 16384.0;  // Convert to g
    *ay = (int16_t)((data[2] << 8) | data[3]) / 16384.0;
    *az = (int16_t)((data[4] << 8) | data[5]) / 16384.0;

    // Basic fall detection: If Z accel drops below -1.5g (simulate fall), trigger help
    if (*az < -1.5) {
        ESP_LOGW(TAG, "Fall detected! Triggering help.");
        // In a real scenario, call show_help_screen() or send POST
    }
}