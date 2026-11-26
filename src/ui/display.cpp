#include <Arduino.h>
#include "config.h"
#include "display.h"

static uint8_t draw_buf[LCD_HOR_RES * BUF_ROWS * 2];
static lv_obj_t* status_label;
static uint32_t tap_count = 0;

static uint32_t lvgl_tick() { return millis(); }

static void button_event_cb(lv_event_t* e) {
    if (lv_event_get_code(e) == LV_EVENT_CLICKED) {
        ++tap_count;

        char text[64];
        snprintf(text, sizeof(text), "Tap detected. Taps: %lu", static_cast<unsigned long>(tap_count));
        lv_label_set_text(status_label, text);
    }
}

void test_ui_init() {
    lv_init();
    lv_tick_set_cb(lvgl_tick);

    lv_display_t* display = lv_lovyan_gfx_create(LCD_HOR_RES, LCD_VER_RES, draw_buf, sizeof(draw_buf), true);
    lv_display_set_rotation(display, LV_DISPLAY_ROTATION_0);

    // Screen title
    lv_obj_t* title = lv_label_create(lv_screen_active());
    lv_label_set_text(title, "UI Display Test");
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -100);

    // Status label
    status_label = lv_label_create(lv_screen_active());
    lv_label_set_text(status_label, "Tap the button below");
    lv_obj_align(status_label, LV_ALIGN_CENTER, 0, -40);

    // Button
    lv_obj_t *button = lv_button_create(lv_screen_active());
    lv_obj_remove_style_all(button);
    lv_obj_set_size(button, 180, 80);
    lv_obj_align(button, LV_ALIGN_CENTER, 0, 50);
    lv_obj_set_style_bg_color(button, lv_palette_main(LV_PALETTE_BLUE), LV_PART_MAIN);
    lv_obj_set_style_bg_opa(button, LV_OPA_COVER, LV_PART_MAIN);
    lv_obj_set_style_pad_all(button, 12, LV_PART_MAIN);
    lv_obj_set_size(button, 180, 80);
    lv_obj_align(button, LV_ALIGN_CENTER, 0, 50);
    lv_obj_add_event_cb(button, button_event_cb, LV_EVENT_CLICKED, NULL);

    // Button text
    lv_obj_t *button_label = lv_label_create(button);
    lv_label_set_text(button_label, "tap me :)");
    lv_obj_center(button_label);
}