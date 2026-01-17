// elder_ui.c
/*#include "elder_ui.h"
#include "esp_log.h"

void show_menu_food() {
    // TODO: Replace with actual touchscreen draw functions
    ESP_LOGI("UI", "Showing FOOD menu on screen");
}

void show_help_screen() {
    ESP_LOGI("UI", "Showing HELP screen on screen");
}

void show_notification(const char* message) {
    ESP_LOGI("UI", "Notification: %s", message);
}
*/
   
#include "elder_ui.h"
#include <stdio.h>

static lv_obj_t * main_screen;

// Helper to create a "Big Button"
static lv_obj_t* create_big_button(lv_obj_t* parent, const char* text, lv_color_t color, lv_event_cb_t cb) {
    lv_obj_t* btn = lv_btn_create(parent);
    lv_obj_set_size(btn, 140, 100); // Large touch target
    lv_obj_set_style_bg_color(btn, color, 0);
    lv_obj_add_event_cb(btn, cb, LV_EVENT_CLICKED, NULL);

    lv_obj_t* label = lv_label_create(btn);
    lv_label_set_text(label, text);
    lv_obj_center(label);
    lv_obj_set_style_text_font(label, &lv_font_montserrat_20, 0); // Large font
    
    return btn;
}

static void food_cb(lv_event_t * e) { show_food_menu(); }
static void help_cb(lv_event_t * e) { show_confirmation("Calling Help..."); }

void show_home_screen(void) {
    lv_obj_clean(lv_scr_act());
    
    // Grid layout for 4 big buttons
    lv_obj_t* cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 320, 240);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(cont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    create_big_button(cont, "FOOD", lv_palette_main(LV_PALETTE_ORANGE), food_cb);
    create_big_button(cont, "CLINIC", lv_palette_main(LV_PALETTE_BLUE), NULL);
    create_big_button(cont, "GROCERY", lv_palette_main(LV_PALETTE_GREEN), NULL);
    create_big_button(cont, "HELP", lv_palette_main(LV_PALETTE_RED), help_cb);
}

void show_food_menu(void) {
    lv_obj_clean(lv_scr_act());
    lv_obj_t* label = lv_label_create(lv_scr_act());
    lv_label_set_text(label, "Choose Lunch:");
    lv_obj_align(label, LV_ALIGN_TOP_MID, 0, 10);

    create_big_button(lv_scr_act(), "Chicken Rice", lv_palette_lighten(LV_PALETTE_AMBER, 1), NULL);
    // Add logic to return home
}

void elder_ui_init(void) {
    show_home_screen();
}