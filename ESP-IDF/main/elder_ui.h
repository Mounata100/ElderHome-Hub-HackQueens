// elder_ui.h
/*#pragma once

void show_menu_food();
void show_help_screen();
void show_notification(const char* message);
*/
#ifndef ELDER_UI_H
#define ELDER_UI_H

#include "lvgl.h"

// Screen states
typedef enum {
    SCREEN_HOME,
    SCREEN_FOOD,
    SCREEN_APPOINTMENT,
    SCREEN_CONFIRMATION
} elder_screen_t;

void elder_ui_init(void);
void show_home_screen(void);
void show_food_menu(void);
void show_confirmation(const char* message);

#endif