#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "wifi.h"
#include "ui.h"
#include "buttons.h"
#include "audio.h"
#include "mpu6050.h"

void app_main(void)
{
    wifi_init();          // Connect to WiFi
    ui_init();            // Big buttons UI
    buttons_init();       // Emergency button
    audio_init();         // Mic + speaker
    mpu6050_init();       // Optional: fall detection

    while (1) {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
