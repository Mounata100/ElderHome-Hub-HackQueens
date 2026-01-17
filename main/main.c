// main.c
/*
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_http_client.h"
#include "esp_wifi.h"
#include "esp_event.h"
#include "nvs_flash.h"

#define BUTTON_GPIO GPIO_NUM_0
#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASSWORD"
#define POST_URL "http://yourserver.com/api/button_press"

static const char* TAG = "ElderHomeHub";

static void wifi_event_handler(void* arg, esp_event_base_t event_base, int32_t event_id, void* event_data) {
    if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
        esp_wifi_connect();
    } else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_DISCONNECTED) {
        ESP_LOGI(TAG, "Disconnected. Reconnecting...");
        esp_wifi_connect();
    } else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
        ESP_LOGI(TAG, "Got IP");
    }
}

static void wifi_init() {
    ESP_ERROR_CHECK(esp_netif_init());
    ESP_ERROR_CHECK(esp_event_loop_create_default());
    esp_netif_create_default_wifi_sta();
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
    ESP_ERROR_CHECK(esp_wifi_init(&cfg));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(WIFI_EVENT, ESP_EVENT_ANY_ID, &wifi_event_handler, NULL, NULL));
    ESP_ERROR_CHECK(esp_event_handler_instance_register(IP_EVENT, IP_EVENT_STA_GOT_IP, &wifi_event_handler, NULL, NULL));
    wifi_config_t wifi_config = {
        .sta = {
            .ssid = WIFI_SSID,
            .password = WIFI_PASS,
        },
    };
    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_start());
}

void send_post() {
    esp_http_client_config_t config = { .url = POST_URL, .method = HTTP_METHOD_POST };
    esp_http_client_handle_t client = esp_http_client_init(&config);
    const char* data = "{\"button\":\"pressed\"}";
    esp_http_client_set_header(client, "Content-Type", "application/json");
    esp_http_client_set_post_field(client, data, strlen(data));
    esp_err_t err = esp_http_client_perform(client);
    if (err == ESP_OK) {
        ESP_LOGI(TAG, "HTTP POST Status = %d", esp_http_client_get_status_code(client));
    } else {
        ESP_LOGE(TAG, "HTTP POST failed: %s", esp_err_to_name(err));
    }
    esp_http_client_cleanup(client);
}

void app_main() {
    nvs_flash_init();
    wifi_init();

    gpio_config_t btn_cfg = {
        .pin_bit_mask = 1ULL << BUTTON_GPIO,
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&btn_cfg);

    while (1) {
        if (gpio_get_level(BUTTON_GPIO) == 0) {
            ESP_LOGI(TAG, "Button pressed");
            send_post();
            vTaskDelay(pdMS_TO_TICKS(1000));  // debounce
        }
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
*/


/*

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_http_client.h"
// Wi-Fi and NVS include when ESP-IDF is ready
//#include "esp_wifi.h"
//#include "esp_event.h"
//#include "nvs_flash.h"

#include "elder_ui.h"
#include "mpu6050.h"

#define BUTTON_ORDER_FOOD GPIO_NUM_0
#define BUTTON_HELP       GPIO_NUM_39

static const char* TAG = "ElderHomeHub";

void app_main() {
    // TODO: Initialize Wi-Fi, NVS (when ESP-IDF ready)

    // Initialize MPU-6050
    mpu6050_init();

    // Initialize buttons
    gpio_config_t btn_cfg = {
        .pin_bit_mask = (1ULL << BUTTON_ORDER_FOOD) | (1ULL << BUTTON_HELP),
        .mode = GPIO_MODE_INPUT,
        .pull_up_en = GPIO_PULLUP_ENABLE,
    };
    gpio_config(&btn_cfg);

    // Main loop
    while (1) {
        // Button logic
        if (gpio_get_level(BUTTON_ORDER_FOOD) == 0) {
            ESP_LOGI(TAG, "Order Food button pressed");
            show_menu_food();
            vTaskDelay(pdMS_TO_TICKS(500)); // debounce
        }

        if (gpio_get_level(BUTTON_HELP) == 0) {
            ESP_LOGI(TAG, "HELP button pressed");
            show_help_screen();
            vTaskDelay(pdMS_TO_TICKS(500));
        }

        // MPU-6050 demo read
        float ax, ay, az;
        mpu6050_read_accel(&ax, &ay, &az);
        ESP_LOGI(TAG, "Accel: X=%.2f Y=%.2f Z=%.2f", ax, ay, az);

        vTaskDelay(pdMS_TO_TICKS(200));
    }
}
*/




#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "bsp/esp-bsp.h" // Specific to ESP32-S3-Box-3
#include "elder_ui.h"

static const char *TAG = "ElderHomeHub";

void app_main(void) {
    /* 1. Initialize I2C and Display */
    bsp_i2c_init();
    bsp_display_start();
    bsp_display_backlight_on();

    /* 2. Initialize LVGL UI */
    elder_ui_init();

    ESP_LOGI(TAG, "ElderHome Hub Started successfully.");

    while (1) {
        // Feed the LVGL timer
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}