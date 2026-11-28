#define TEST_LOGGER // TEST_UI or TEST_WIFI or TEST_LOGGER

#include <Arduino.h>
#include "config.h"
#include <SD.h>


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

#ifdef TEST_LOGGER
#include "storage/logger.h"

const int chipSelect = SD_CS;
SPIClass sdSPI(FSPI);

void setup() {
    Serial.begin(115200);
    delay(5000);
    Serial.println("Initializing SD card...");
    sdSPI.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
    if (!SD.begin(chipSelect, sdSPI)) {
        Serial.println("initialization failure!");
    } else {
        write_file();
        Serial.println("Initialization done.");
    }
}

void loop() {
    Serial.println("finished!");
    delay(500);
}

#endif