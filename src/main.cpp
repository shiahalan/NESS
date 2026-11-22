#include <Arduino.h>
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

