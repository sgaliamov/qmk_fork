// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include <stdbool.h>
#include <stdint.h>

void     custom_magic_reset(void);
uint16_t custom_magic_keycode(uint8_t layer, uint8_t row, uint8_t col);
bool     custom_magic_led_state(void);
