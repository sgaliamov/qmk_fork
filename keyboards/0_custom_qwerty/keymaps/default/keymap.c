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
    TEMP_EN,
    DASH_W,
    DASH_A,
    DASH_S,
    DASH_D,
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
        TD(TD_LALT), MO(_FN),     KC_APP,      KC_LCMD,     TD(TD_LCTL), KC_SPC,      TD(TD_LSFT), KC_BSLS,             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TEMP_EN,     KC_DOWN
    ),

    [_FN] = LAYOUT(
        KC_ESC,      KC_F1,       KC_F2,       KC_F3,       KC_F4,       KC_F5,       XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_F8,       KC_F9,       KC_F10,      KC_F11,      KC_F12,      KC_PSCR,
        KC_GRV,      KC_1,        KC_2,        KC_3,        KC_4,        KC_5,        KC_F6,       XXXXXXX,             XXXXXXX,     KC_F7,       KC_6,        KC_7,        KC_8,        KC_9,        KC_0,        KC_RBRC,
        KC_TAB,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     TD_TOGGLE,   TG(_FGHT),   XXXXXXX,             XXXXXXX,     KC_NUM,      KC_P0,       KC_P1,       KC_P2,       KC_P3,       XXXXXXX,     KC_LBRC,
        KC_PEQL,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_SLSH,     KC_HOME,             KC_PGUP,     KC_QUOT,     ARROW_FAT,   KC_P4,       KC_P5,       KC_P6,       KC_SCLN,     KC_PEQL,
        KC_DEL,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     KC_MINS,     KC_END,              KC_PGDN,     KC_EQL,      ARROW_THIN,  KC_P7,       KC_P8,       KC_P9,       KC_UP,       KC_BSPC,
        TD(TD_LALT), MO(_FN),     KC_APP,      KC_LCMD,     TD(TD_LCTL), KC_SPC,      TD(TD_LSFT), KC_BSLS,             KC_INS,      TD(TD_RSFT), KC_SPC,      TD(TD_RCTL), KC_LEFT,     KC_RGHT,     TEMP_EN,     KC_RALT
    ),

    [_FGHT] = LAYOUT(
        KC_ESC,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
        XXXXXXX,     XXXXXXX,     DASH_W,      XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,
        XXXXXXX,     UP_LEFT,     KC_W,        UP_RIGHT,    XXXXXXX,     XXXXXXX,     TG(_FGHT),   XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_O,        KC_U,        KC_I,        KC_P,        XXXXXXX,     XXXXXXX,
        DASH_A,      KC_A,        KC_S,        KC_D,        DASH_D,      XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_L,        KC_J,        KC_K,        KC_SCLN,     XXXXXXX,     KC_ENT,
        XXXXXXX,     DOWN_LEFT,   DASH_S,      DOWN_RIGHT,  XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,             XXXXXXX,     XXXXXXX,     KC_V,        KC_C,        KC_N,        KC_B,        XXXXXXX,     XXXXXXX,
        KC_LALT,     XXXXXXX,     XXXXXXX,     DASH_W,      KC_W,        KC_C,        KC_C,        XXXXXXX,             XXXXXXX,     KC_N,        KC_N,        XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX,     XXXXXXX
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

/** Classify a modifier gesture by tap count and whether the key is still down. */
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

/** Set the indicator brightness for the fighting layer, once PWM is ready. */
static void led_indicator_update(layer_state_t state) {
    if (LED_PWM_DRIVER.state != PWM_READY) return;

    if (IS_LAYER_ON_STATE(state, _FGHT)) {
        pwmEnableChannel(&LED_PWM_DRIVER, LED_PWM_CHANNEL, LED_PWM_FIGHT);
    } else {
        pwmDisableChannel(&LED_PWM_DRIVER, LED_PWM_CHANNEL);
    }
}

/** Refresh the indicator on layer changes without modifying the layer state. */
layer_state_t layer_state_set_user(layer_state_t state) {
    led_indicator_update(state);
    return state;
}

/** Initialize the indicator pin and PWM driver after keyboard startup. */
void keyboard_post_init_user(void) {
    palSetLineMode(LED_INDICATOR_PIN, PAL_MODE_ALTERNATE_PWM);
    pwmStart(&LED_PWM_DRIVER, &led_pwm_cfg);
    led_indicator_update(layer_state);
}

/** Emit modifier taps or register the modifier combination for a resolved hold. */
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

/** Release the modifiers owned by the completed tap dance and reset its state. */
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

// Dash timing, in milliseconds:
//   tap:  down --2 ms-- up --4 ms-- down --at least 2 ms-- up
//   hold: down --2 ms-- up --4 ms-- down until physical release
// The second press IS the hold: there is no third press or hold threshold.
// If released early, finish both presses anyway. If still held, the second
// press lasts until release, just like a normal key. Scan scheduling and USB
// polling can extend these minimum durations slightly.
#define DASH_PRESS_MS 2
#define DASH_GAP_MS   4

typedef enum {
    DASH_IDLE,
    DASH_WAIT_SECOND,
    DASH_SECOND_DOWN,
    DASH_WAIT_NEXT,
} dash_phase_t;

typedef struct {
    uint16_t     started; // Start of the current gap or second press.
    uint16_t     queued;  // Rapid re-presses received before this pair finished.
    uint8_t      keycode;
    bool         pressed; // Physical state, independent of pending output.
    dash_phase_t phase;
} dash_state_t;

// Track physical positions so duplicate bindings and layer changes are safe.
static dash_state_t dash_keys[MATRIX_ROWS][MATRIX_COLS];
static uint8_t normal_movement_keys[MATRIX_ROWS][MATRIX_COLS];
static uint8_t movement_holds[4];

/** Map a movement key (W, A, S, or D only) to its shared hold counter. */
static uint8_t movement_index(uint8_t keycode) {
    switch (keycode) {
        case KC_W: return 0;
        case KC_A: return 1;
        case KC_S: return 2;
        default:   return 3; // KC_D
    }
}

/** Acquire a shared direction and ensure it is down, including after a dash gap. */
static void movement_press(uint8_t keycode) {
    movement_holds[movement_index(keycode)]++;
    register_code(keycode);
}

/** Release a direction only when no normal key, diagonal, or dash owns it. */
static void movement_release(uint8_t keycode) {
    uint8_t *holds = &movement_holds[movement_index(keycode)];
    if (*holds && --(*holds) == 0) unregister_code(keycode);
}

/** Send the first short press, then schedule the gap before the second press. */
static void dash_start(dash_state_t *dash) {
    if (movement_holds[movement_index(dash->keycode)] != 0) {
        // Re-trigger a direction already held by another key. Preserve its
        // logical ownership; the second press restores the shared direction.
        unregister_code(dash->keycode);
        wait_ms(DASH_GAP_MS);
    }
    tap_code_delay(dash->keycode, DASH_PRESS_MS);
    dash->started = timer_read();
    dash->phase = DASH_WAIT_SECOND;
}

/** Start one dash per physical press, queuing unusually rapid re-presses. */
static void dash_press(dash_state_t *dash, uint8_t keycode) {
    if (dash->pressed) return;
    dash->pressed = true;
    if (dash->phase == DASH_IDLE) {
        dash->keycode = keycode;
        dash->queued = 0;
        dash_start(dash);
    } else {
        // Preserve a new tap even if the preceding pair has not finished yet.
        dash->queued++;
    }
}

/** End the second press and leave an inter-pair gap if another dash is queued. */
static void dash_finish(dash_state_t *dash) {
    movement_release(dash->keycode);
    dash->started = timer_read();
    dash->phase = dash->queued ? DASH_WAIT_NEXT : DASH_IDLE;
}

/** Release immediately unless the second press still needs its minimum duration. */
static void dash_release(dash_state_t *dash) {
    dash->pressed = false;
    if (dash->phase == DASH_SECOND_DOWN && timer_elapsed(dash->started) >= DASH_PRESS_MS) {
        dash_finish(dash);
    }
    // A release before the second tap must not cancel that tap.
}

/** Advance scheduled output; only the short first-press pulse uses blocking waits. */
void matrix_scan_user(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            dash_state_t *dash = &dash_keys[row][col];
            uint16_t elapsed = timer_elapsed(dash->started);
            if (dash->phase == DASH_WAIT_SECOND && elapsed >= DASH_GAP_MS) {
                // Leave the second press down while physically held; never
                // release and re-register it to enter a separate hold state.
                movement_press(dash->keycode);
                dash->started = timer_read();
                dash->phase = DASH_SECOND_DOWN;
            } else if (dash->phase == DASH_SECOND_DOWN && elapsed >= DASH_PRESS_MS) {
                if (!dash->pressed || dash->queued) {
                    dash_finish(dash);
                }
            } else if (dash->phase == DASH_WAIT_NEXT && elapsed >= DASH_GAP_MS) {
                dash->queued--;
                dash_start(dash);
            }
        }
    }
}

/** Route position-tracked movement releases, dash presses, and other custom keys. */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.key.row < MATRIX_ROWS && record->event.key.col < MATRIX_COLS) {
        dash_state_t *dash = &dash_keys[record->event.key.row][record->event.key.col];
        if (!record->event.pressed && dash->pressed) {
            dash_release(dash);
            return false;
        }
        uint8_t *normal_movement = &normal_movement_keys[record->event.key.row][record->event.key.col];
        if (!record->event.pressed && *normal_movement != KC_NO) {
            movement_release(*normal_movement);
            *normal_movement = KC_NO;
            return false;
        }
        if (record->event.pressed && IS_LAYER_ON(_FGHT) && (keycode == KC_W || keycode == KC_A || keycode == KC_S || keycode == KC_D)) {
            *normal_movement = keycode;
            movement_press(keycode);
            return false;
        }
    }

    switch (keycode) {
        case DASH_W:
        case DASH_A:
        case DASH_S:
        case DASH_D: {
            if (record->event.pressed && record->event.key.row < MATRIX_ROWS && record->event.key.col < MATRIX_COLS) {
                static const uint8_t keys[] = {KC_W, KC_A, KC_S, KC_D};
                dash_press(&dash_keys[record->event.key.row][record->event.key.col], keys[keycode - DASH_W]);
            }
            return false;
        }

        case TEMP_EN:
            // Switch the OS input method on press and restore it on release.
            tap_code16(LGUI(KC_SPC));
            return false;

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
                movement_press(KC_W);
                movement_press(KC_A);
            } else {
                movement_release(KC_A);
                movement_release(KC_W);
            }
            return false;

        case UP_RIGHT:
            if (record->event.pressed) {
                movement_press(KC_W);
                movement_press(KC_D);
            } else {
                movement_release(KC_D);
                movement_release(KC_W);
            }
            return false;

        case DOWN_LEFT:
            if (record->event.pressed) {
                movement_press(KC_S);
                movement_press(KC_A);
            } else {
                movement_release(KC_A);
                movement_release(KC_S);
            }
            return false;

        case DOWN_RIGHT:
            if (record->event.pressed) {
                movement_press(KC_S);
                movement_press(KC_D);
            } else {
                movement_release(KC_D);
                movement_release(KC_S);
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
