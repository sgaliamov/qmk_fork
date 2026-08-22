// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN
};

enum custom_keycodes {
    ARROW_FAT = QK_USER,
    ARROW_THIN,
    QUOT_SWAP,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_BSLS,     KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_LBRC,
        KC_ENT,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_ENT,
        KC_DEL,      KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_UP,       KC_BSPC,
        KC_LALT,     KC_TAB,      KC_APP,      KC_LCMD,     KC_LCTL,     KC_SPC,      KC_LSFT,     MO(_FN),             KC_INS,      KC_RSFT,     KC_SPC,      KC_RCTL,     KC_LEFT,     KC_RGHT,     KC_RALT,     KC_DOWN
),

    [_FN] = LAYOUT(
        _______,     _______,     _______,     _______,     _______,     _______,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     _______,     _______,     _______,     _______,     _______,     _______,
        _______,     KC_P1,       KC_P2,       KC_P3,       KC_P4,       KC_P5,       _______,     XXXXXXX,             XXXXXXX,     _______,     KC_P6,       KC_P7,       KC_P8,       KC_P9,       KC_P0,       _______,
        _______,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_NUM,      XXXXXXX,             XXXXXXX,     _______,     KC_VOLU,     KC_MPRV,     KC_MNXT,     XXXXXXX,     XXXXXXX,     _______,
        _______,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     _______,     _______,             _______,     _______,     KC_VOLD,     ARROW_FAT,   ARROW_THIN,  XXXXXXX,     _______,     _______,
        _______,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     _______,     _______,             _______,     _______,     XXXXXXX,     XXXXXXX,     _______,     _______,     _______,     _______,
        _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______,             _______,     _______,     _______,     _______,     _______,     _______,     _______,     _______
    )
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ARROW_FAT:
            if (record->event.pressed) SEND_STRING("=>");
            return false;

        case ARROW_THIN:
            if (record->event.pressed) SEND_STRING("->");
            return false;

        case QUOT_SWAP:
            if (record->event.pressed) {
                uint8_t shift = get_mods() & MOD_MASK_SHIFT;
                if (shift) {
                    unregister_mods(shift);
                    tap_code(KC_QUOT);
                    register_mods(shift);
                } else {
                    tap_code16(S(KC_QUOT));
                }
            }
            return false;
    }
    return true;
}
