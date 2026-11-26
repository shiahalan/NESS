#pragma once

// ===================================
// LCD Pin Definitions
// ===================================

// LCD SPI pins
#define SPI_MISO 42
#define SPI_MOSI 2
#define SPI_SCLK 1

// LCD control pins
#define LCD_CS  39
#define LCD_DC  41
#define LCD_RST 40
#define LCD_BL  6

// Touchscreen pins (FT6336U)
#define TP_INT 17
#define TP_RST 16
#define TP_SDA 15
#define TP_SCL 7

// LCD resolution
#define LCD_HOR_RES 320
#define LCD_VER_RES 480