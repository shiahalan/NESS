#include <Arduino.h>
#include "wifi/wifi_scanner.h"

void setup() {
    Serial.begin(115200);
    delay(500);
    startWiFiScanner();

    // DISPLAY TEST
    display.initialize();
    fill_color_test(display);
}

void loop() {
    scanForNetworks();
    delay(10000);
    
    // DISPLAY TEST
    // poll_and_draw(display);
    // delay(10);
}

