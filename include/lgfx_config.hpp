#pragma once

#include <LovyanGFX.hpp>
#include "config.h"

// ===================================
// LCD Configs for LGFX
// ===================================

// SPI Bus
#define SPI_MODE 0
#define SPI_FREQ_READ 40000000
#define SPI_FREQ_WRITE 8000000

// Touch controller
#define TP_SPI_ADDR 0x38
#define TP_SPI_FREQ 100000

// ===================================
// LCD lgfx Class for LGFX
// ===================================
class LGFX : public lgfx::LGFX_Device {
    lgfx::Panel_ST7796 _panel_instance {}; // Display controller: ST7796S
    lgfx::Bus_SPI      _bus_instance   {}; // Display communication: SPI
    lgfx::Touch_FT5x06 _touch_instance {}; // Touchscreen controller: FT6336U, support via FT5x06 driver
    lgfx::Light_PWM    _light_instance {}; // Backlight controller
public:
    LGFX();
};

LGFX::LGFX() {
    {
    auto cfg = _bus_instance.config();

    cfg.spi_host    = SPI2_HOST;
    cfg.spi_mode    = SPI_MODE;
    cfg.freq_write  = SPI_FREQ_WRITE;
    cfg.freq_read   = SPI_FREQ_READ;
    cfg.spi_3wire   = false;
    cfg.use_lock    = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;

    cfg.pin_sclk = SPI_SCLK;
    cfg.pin_mosi = SPI_MOSI;
    cfg.pin_miso = SPI_MISO;
    cfg.pin_dc   = LCD_DC;

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
    } { // LCD Panel Config
    auto cfg = _panel_instance.config();

    cfg.pin_cs  = LCD_CS;
    cfg.pin_rst = LCD_RST;

    cfg.pin_busy = -1;
    cfg.panel_width  = LCD_HOR_RES;
    cfg.panel_height = LCD_VER_RES;
    cfg.offset_x = 0;
    cfg.offset_y = 0;
    cfg.offset_rotation = 0;

    cfg.readable = true;
    cfg.invert = true;     // NOTE: Colors are inverted on this display
    cfg.rgb_order = false;
    cfg.bus_shared = false;

    _panel_instance.config(cfg);
    } { // Touchscreen Config (FT6336U)
    auto cfg = _touch_instance.config();

    cfg.x_min = 0;
    cfg.x_max = LCD_HOR_RES - 1;
    cfg.y_min = 0;
    cfg.y_max = LCD_VER_RES - 1;

    cfg.pin_int = TP_INT;
    cfg.pin_rst = TP_RST;

    cfg.bus_shared = false;
    cfg.offset_rotation = 0;

    cfg.i2c_port = 0;
    cfg.i2c_addr = TP_SPI_ADDR;
    cfg.pin_sda = TP_SDA;
    cfg.pin_scl = TP_SCL;
    cfg.freq = TP_SPI_FREQ;

    _touch_instance.config(cfg);
    _panel_instance.setTouch(&_touch_instance);
    } { // Backlight Config
    auto cfg = _light_instance.config();

    cfg.pin_bl = LCD_BL;
    cfg.invert = false;
    cfg.freq = 44100;
    cfg.pwm_channel = 7;

    _light_instance.config(cfg);
    _panel_instance.setLight(&_light_instance);
    }

    setPanel(&_panel_instance);
}