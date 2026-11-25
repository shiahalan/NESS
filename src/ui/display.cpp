#include "display.h"
#include "../../include/config.h"
#include <Arduino.h>

void Display::configure_spi_bus() {
    auto cfg = _bus_instance.config();

    cfg.spi_host    = SPI2_HOST;
    cfg.spi_mode    = SPI_MODE;
    cfg.freq_write  = SPI_FREQ_READ;
    cfg.freq_read   = SPI_FREQ_WRITE;
    cfg.spi_3wire   = false;
    cfg.use_lock    = true;
    cfg.dma_channel = SPI_DMA_CH_AUTO;

    cfg.pin_sclk = SPI_SCLK;
    cfg.pin_mosi = SPI_MOSI;
    cfg.pin_miso = SPI_MISO;
    cfg.pin_dc   = LCD_DC;

    _bus_instance.config(cfg);
    _panel_instance.setBus(&_bus_instance);
}

void Display::configure_lcd_panel() { // LCD Panel Config
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
}

void Display::configure_touch_controller() { // Touchscreen Config (FT6336U)
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
}

void Display::initialize() {
    // Reset FT6336U touch controller
    pinMode(TP_RST, OUTPUT);
    digitalWrite(TP_RST, LOW);  delay(10);
    digitalWrite(TP_RST, HIGH); delay(200);

    // Turn on display
    init();
    setRotation(0);
    pinMode(LCD_BL, OUTPUT); // Enable backlight
    digitalWrite(LCD_BL, HIGH);
}

Display::Display() {
    configure_spi_bus();
    configure_lcd_panel();
    configure_touch_controller();

    setPanel(&_panel_instance);
}

void fill_color_test(Display display) {
    display.fillScreen(TFT_WHITE); delay(1000);
    display.fillScreen(TFT_RED);   delay(1000);
    display.fillScreen(TFT_GREEN); delay(1000);
    display.fillScreen(TFT_BLUE);  delay(1000);
    display.fillScreen(TFT_WHITE);
}
void poll_and_draw(Display display) {
    int32_t x, y;
    if (display.getTouch(&x, &y))
        display.drawCircle(x, y, 2, TFT_RED);
}
