// Copyright 2026 Anzood
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// YD-RP2040: double press of RST enters the UF2 bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
// The blue LED blinks while the double press waits
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

// On-board WS2812 (GP23), driven directly by the keymap without RGBLIGHT
#define WS2812_LED_COUNT 1

// OLED 0.96" 128x64 SSD1306 on I2C1 (see Kryla docs/rev1-wiring.md)
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP2
#define I2C1_SCL_PIN GP3
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_ADDRESS 0x3C
