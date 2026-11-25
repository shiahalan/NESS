#define TEST_UI

#include <Arduino.h>
#include "wifi/wifi_scanner.h"
#include "ui/display.h"

Display display {};

#ifdef TEST_WIFI
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
void setup() {
    Serial.begin(115200);
    delay(500);
    display.initialize();
    fill_color_test(display);
    Serial.println("Finished setup");
}
void loop() {
    poll_and_draw(display);
    delay(10);
}
#endif