// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "custom_magic.h"
#include <string.h>

static bool indicator;

static void gpio_set_pin_output(uint8_t pin) {}
static void gpio_write_pin(uint8_t pin, bool state) {
    indicator = state;
}
static void gpio_write_pin_low(uint8_t pin) {
    indicator = false;
}

// Host adapter for the board's row-major 6x16 layout and indicator GPIO.
#define GP17 17
#define QMK_KEYBOARD_H "quantum.h"
// clang-format off
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f, \
    k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f, \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, \
    k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f, \
    k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a, k5b, k5c, k5d, k5e, k5f \
) { \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, k0f}, \
    {k10, k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, k2e, k2f}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48, k49, k4a, k4b, k4c, k4d, k4e, k4f}, \
    {k50, k51, k52, k53, k54, k55, k56, k57, k58, k59, k5a, k5b, k5c, k5d, k5e, k5f} \
}
// clang-format on

#define keymaps custom_magic_keymaps
#include "keyboards/0_custom_magic/keymaps/default/keymap.c"
#undef keymaps

void custom_magic_reset(void) {
    tap_dance_enabled = true;
    qwerty_selected   = false;
    memset(qwerty_holds, 0, sizeof(qwerty_holds));
    indicator = false;
}

uint16_t custom_magic_keycode(uint8_t layer, uint8_t row, uint8_t col) {
    return pgm_read_word(&custom_magic_keymaps[layer][row][col]);
}

bool custom_magic_led_state(void) {
    return indicator;
}
