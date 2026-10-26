// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _BASE,
    _FN,
    _FGHT
};

enum custom_keycodes {
    ARROW_FAT = QK_USER,
    ARROW_THIN,
    QUOT_SWAP,
    TD_TOGGLE,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
};

// Layer-indicator LED on GP17, driven by RP2040 PWM slice 0 channel B.
#define LED_INDICATOR_PIN GP17
#define LED_PWM_DRIVER   PWMD0
#define LED_PWM_CHANNEL  1
#define LED_PWM_PERIOD   256
#define LED_PWM_FIGHT    80

enum tap_dances {
    TD_LSFT,
    TD_RSFT,
    TD_LALT,
    TD_LCTL,
    TD_RCTL,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      KC_Q,        KC_W,        KC_E,        KC_R,        KC_T,        KC_CAPS,     XXXXXXX,             XXXXXXX,     KC_PAUS,     KC_Y,        KC_U,        KC_I,        KC_O,        KC_P,        KC_LBRC,
        KC_ENT,      KC_A,        KC_S,        KC_D,        KC_F,        KC_G,        KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     KC_H,        KC_J,        KC_K,        KC_L,        KC_SCLN,     KC_ENT,
        KC_DEL,      KC_Z,        KC_X,        KC_C,        KC_V,        KC_B,        KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      KC_N,        KC_M,        KC_COMM,     KC_DOT,      KC_UP,       KC_BSPC,
        TD(TD_LALT), MO(_FN),     KC_APP,      KC_LCMD,     TD(TD_LCTL), KC_SPC,      TD(TD_LSFT), KC_BSLS,             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     KC_DOWN,     TD(TD_LALT)
    ),

    [_FN] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     TD_TOGGLE,   TG(_FGHT),   XXXXXXX,             XXXXXXX,     KC_NUM,      KC_P0,       KC_P1,       KC_P2,       KC_P3,       XXXXXXX,     KC_LBRC,
        KC_PEQL,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     ARROW_FAT,   KC_P4,       KC_P5,       KC_P6,       KC_SCLN,     KC_PEQL,
        KC_DEL,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      ARROW_THIN,  KC_P7,       KC_P8,       KC_P9,       KC_UP,       KC_BSPC,
        TD(TD_LALT), MO(_FN),     KC_APP,      KC_LCMD,     TD(TD_LCTL), KC_SPC,      TD(TD_LSFT), KC_BSLS,             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     KC_RALT,     KC_DOWN
    ),

    [_FGHT] = LAYOUT(
        KC_ESC,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
        XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
        XXXXXXX,     UP_LEFT,     UP_LEFT,     UP_RIGHT,    UP_RIGHT,    XXXXXXX,     TG(_FGHT),   XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_O,        KC_U,        KC_I,        KC_P,        XXXXXXX,     XXXXXXX,
        XXXXXXX,     KC_W,        KC_A,        KC_D,        KC_S,        XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_L,        KC_J,        KC_K,        KC_SCLN,     XXXXXXX,     KC_ENT,
        XXXXXXX,     DOWN_LEFT,   DOWN_LEFT,   DOWN_RIGHT,  DOWN_RIGHT,  XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_V,        KC_C,        KC_N,        KC_B,        XXXXXXX,     XXXXXXX,
        KC_LALT,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_LCTL,     KC_SPC,      KC_LSFT,     XXXXXXX,             XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX
    )
};

// clang-format on

typedef enum {
    MOD_TD_NONE,
    MOD_TD_SINGLE_TAP,
    MOD_TD_SINGLE_HOLD,
    MOD_TD_DOUBLE_TAP,
    MOD_TD_DOUBLE_HOLD,
} mod_td_state_t;

typedef struct {
    mod_td_state_t state;
    uint16_t       base_kc;
    uint8_t        combo_mods;
} mod_td_user_data_t;

static mod_td_user_data_t lctl_td_data = {MOD_TD_NONE, KC_LCTL, MOD_BIT(KC_LSFT) | MOD_BIT(KC_LCTL)};
static mod_td_user_data_t rctl_td_data = {MOD_TD_NONE, KC_RCTL, MOD_BIT(KC_RSFT) | MOD_BIT(KC_RCTL)};
static mod_td_user_data_t lsft_td_data = {MOD_TD_NONE, KC_LSFT, MOD_BIT(KC_LALT) | MOD_BIT(KC_LSFT)};
static mod_td_user_data_t rsft_td_data = {MOD_TD_NONE, KC_RSFT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RSFT)};
static mod_td_user_data_t lalt_td_data = {MOD_TD_NONE, KC_LALT, MOD_BIT(KC_LALT) | MOD_BIT(KC_RCTL)};

static mod_td_state_t resolve_mod_td(tap_dance_state_t *state) {
    if (state->count == 1) return state->pressed ? MOD_TD_SINGLE_HOLD : MOD_TD_SINGLE_TAP;
    if (state->count == 2) return state->pressed ? MOD_TD_DOUBLE_HOLD : MOD_TD_DOUBLE_TAP;
    return MOD_TD_NONE;
}

static bool tap_dance_enabled = true;

void mod_td_finished(tap_dance_state_t *state, void *user_data);
void mod_td_reset(tap_dance_state_t *state, void *user_data);

tap_dance_action_t tap_dance_actions[] = {
    [TD_LSFT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lsft_td_data},
    [TD_RSFT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rsft_td_data},
    [TD_LALT] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lalt_td_data},
    [TD_LCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &lctl_td_data},
    [TD_RCTL] = {.fn = {NULL, mod_td_finished, mod_td_reset}, .user_data = &rctl_td_data},
};

static PWMConfig led_pwm_cfg = {
    .frequency = 1000000,
    .period    = LED_PWM_PERIOD,
    .channels  = {
        [0] = {.mode = PWM_OUTPUT_DISABLED},
        [1] = {.mode = PWM_OUTPUT_ACTIVE_HIGH},
    },
};

static void led_indicator_update(layer_state_t state) {
    if (LED_PWM_DRIVER.state != PWM_READY) return;

    if (IS_LAYER_ON_STATE(state, _FGHT)) {
        pwmEnableChannel(&LED_PWM_DRIVER, LED_PWM_CHANNEL, LED_PWM_FIGHT);
    } else {
        pwmDisableChannel(&LED_PWM_DRIVER, LED_PWM_CHANNEL);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    led_indicator_update(state);
    return state;
}

void keyboard_post_init_user(void) {
    palSetLineMode(LED_INDICATOR_PIN, PAL_MODE_ALTERNATE_PWM);
    pwmStart(&LED_PWM_DRIVER, &led_pwm_cfg);
    led_indicator_update(layer_state);
}

void mod_td_finished(tap_dance_state_t *state, void *user_data) {
    mod_td_user_data_t *td = (mod_td_user_data_t *)user_data;
    td->state = resolve_mod_td(state);

    switch (td->state) {
        case MOD_TD_SINGLE_TAP:
            tap_code(td->base_kc);
            break;
        case MOD_TD_SINGLE_HOLD:
            register_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_TAP:
            tap_code(td->base_kc);
            tap_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_HOLD:
            register_mods(td->combo_mods);
            break;
        default:
            break;
    }
}

void mod_td_reset(tap_dance_state_t *state, void *user_data) {
    mod_td_user_data_t *td = (mod_td_user_data_t *)user_data;
    switch (td->state) {
        case MOD_TD_SINGLE_HOLD:
            unregister_code(td->base_kc);
            break;
        case MOD_TD_DOUBLE_HOLD:
            unregister_mods(td->combo_mods);
            break;
        default:
            break;
    }
    td->state = MOD_TD_NONE;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case TD(TD_LSFT):
        case TD(TD_RSFT):
        case TD(TD_LALT):
        case TD(TD_LCTL):
        case TD(TD_RCTL):
            if (!tap_dance_enabled) {
                mod_td_user_data_t *td = (mod_td_user_data_t *)tap_dance_actions[TD_INDEX(keycode)].user_data;
                if (record->event.pressed) {
                    register_code(td->base_kc);
                    return false;
                }
                unregister_code(td->base_kc);
                return false;
            }
            return true;

        case ARROW_FAT:
            if (record->event.pressed) SEND_STRING("=>");
            return false;

        case ARROW_THIN:
            if (record->event.pressed) SEND_STRING("->");
            return false;

        case UP_LEFT:
            if (record->event.pressed) {
                register_code(KC_W);
                register_code(KC_A);
            } else {
                unregister_code(KC_A);
                unregister_code(KC_W);
            }
            return false;

        case UP_RIGHT:
            if (record->event.pressed) {
                register_code(KC_W);
                register_code(KC_D);
            } else {
                unregister_code(KC_D);
                unregister_code(KC_W);
            }
            return false;

        case DOWN_LEFT:
            if (record->event.pressed) {
                register_code(KC_S);
                register_code(KC_A);
            } else {
                unregister_code(KC_A);
                unregister_code(KC_S);
            }
            return false;

        case DOWN_RIGHT:
            if (record->event.pressed) {
                register_code(KC_S);
                register_code(KC_D);
            } else {
                unregister_code(KC_D);
                unregister_code(KC_S);
            }
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

        case TD_TOGGLE:
            if (record->event.pressed) {
                tap_dance_enabled = !tap_dance_enabled;
            }
            return false;
    }
    return true;
}
