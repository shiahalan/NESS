#include <Arduino.h>
#include <SD.h>
#include "logger.h"

void write_file() {
    File file = SD.open("test.txt", FILE_WRITE);
    if (file) {
        file.println("hello");
        file.flush();
        file.close();
    }
}