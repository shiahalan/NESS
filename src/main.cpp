#define TEST_UI // TEST_UI or TEST_WIFI

#include <Arduino.h>


#ifdef TEST_WIFI
#include "wifi/wifi_scanner.h"
void setup() {
    Serial.begin(115200);
    delay(500);

    startWiFiScanner();
}

void loop() {
    scanForNetworks();
    delay(10000);
}
#endif

#ifdef TEST_UI
#include "ui/display.h"
void setup() {
    Serial.begin(115200);
    delay(500);
    Serial.println("Starting LVGL.");

    test_ui_init();

    Serial.println("LVGL initialization finished.");
}

void loop() {
    lv_timer_handler();
    delay(1);
}
#endif