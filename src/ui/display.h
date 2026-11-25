#pragma once

#include <LovyanGFX.hpp>

// LCD resolution
#define LCD_HOR_RES 320
#define LCD_VER_RES 480

// SPI Bus
#define SPI_MODE 0
#define SPI_FREQ_READ 40000000
#define SPI_FREQ_WRITE 16000000

// Touch controller
#define TP_SPI_ADDR 0x38
#define TP_SPI_FREQ 100000

// Display class, this is our interface when working with the display.
class Display : public lgfx::LGFX_Device {
    lgfx::Panel_ST7796 _panel_instance {}; // Display controller: ST7796S
    lgfx::Bus_SPI      _bus_instance   {}; // Display communication: SPI
    lgfx::Touch_FT5x06 _touch_instance {}; // Touchscreen controller: FT6336U, support via FT5x06 driver

    void configure_spi_bus();
    void configure_lcd_panel();
    void configure_touch_controller();
public:
    Display();
    void initialize();
};

void fill_color_test(Display& display);
void poll_and_draw(Display& display);